#include "pintura.h"

#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

Pintura::Pintura(int idUser, Database *base, QWidget *parent)
    : QWidget(parent)
{
    // Se guarda el usuario para asociar todos los trazos a su cuenta.
    idUsuario = idUser;
    db = base;

    dibujando = false;
    colorActual = Qt::black;
    grosorActual = 3;
    accionesDeshechas = 0;

    setFocusPolicy(Qt::StrongFocus);
    setMinimumSize(800, 600);
    setStyleSheet("background-color: white;");
}

void Pintura::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    // Primero se dibujan los trazos ya confirmados.
    for (int i = 0; i < trazos.size(); i++) {

        painter.setPen(
            QPen(trazos[i].color,
                 trazos[i].grosor,
                 Qt::SolidLine,
                 Qt::RoundCap,
                 Qt::RoundJoin)
            );

        for (int j = 1; j < trazos[i].puntos.size(); j++) {

            painter.drawLine(
                trazos[i].puntos[j - 1],
                trazos[i].puntos[j]
                );
        }
    }

    painter.setPen(
        QPen(colorActual,
             grosorActual,
             Qt::SolidLine,
             Qt::RoundCap,
             Qt::RoundJoin)
        );

    // Luego se dibuja el trazo que esta creando el usuario.
    for (int i = 1; i < trazoActual.puntos.size(); i++) {

        painter.drawLine(
            trazoActual.puntos[i - 1],
            trazoActual.puntos[i]
            );
    }
}

void Pintura::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

        // Al presionar el mouse comienza un trazo nuevo.
        dibujando = true;

        trazoActual.puntos.clear();

        trazoActual.color = colorActual;

        trazoActual.grosor = grosorActual;

        trazoActual.puntos.push_back(event->pos());
    }
}

void Pintura::mouseMoveEvent(QMouseEvent *event)
{
    if (dibujando) {

        // Cada movimiento agrega un punto a la linea actual.
        trazoActual.puntos.push_back(event->pos());

        update();
    }
}

void Pintura::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && dibujando) {

        // Al soltar el mouse el trazo se confirma y se guarda.
        dibujando = false;

        trazos.push_back(trazoActual);

        guardarTrazoActual();

        trazoActual.puntos.clear();

        update();
    }
}

void Pintura::wheelEvent(QWheelEvent *event)
{
    // La rueda del mouse cambia el grosor del pincel.
    int delta = event->angleDelta().y();

    if (delta > 0) {

        grosorActual++;
    }
    else {

        if (grosorActual > 1) {

            grosorActual--;
        }
    }

    update();
}

void Pintura::keyPressEvent(QKeyEvent *event)
{
    // Atajos de teclado para cambiar color, borrar todo o deshacer.
    if (event->key() == Qt::Key_R) {

        colorActual = Qt::red;
    }

    if (event->key() == Qt::Key_G) {

        colorActual = Qt::green;
    }

    if (event->key() == Qt::Key_B) {

        colorActual = Qt::blue;
    }

    if (event->key() == Qt::Key_Escape) {

        trazos.clear();
        accionesDeshechas = 0;

        if (db != nullptr) {
            db->borrarTrazosUsuario(idUsuario);
        }

        update();
    }

    if (event->modifiers() == Qt::ControlModifier &&
        event->key() == Qt::Key_Z) {

        if (!trazos.isEmpty() && accionesDeshechas < 10) {

            trazos.removeLast();
            accionesDeshechas++;

            if (db != nullptr) {
                db->borrarTrazosUsuario(idUsuario);

                // Se regraba la base con la lista de trazos que quedaron tras deshacer.
                for (int i = 0; i < trazos.size(); i++) {

                    int idTrazo = db->guardarTrazo(
                        idUsuario,
                        trazos[i].color,
                        trazos[i].grosor
                        );

                    for (int j = 0; j < trazos[i].puntos.size(); j++) {
                        db->guardarCoordenada(
                            idTrazo,
                            trazos[i].puntos[j],
                            j
                            );
                    }
                }
            }

            update();
        }
    }
}

void Pintura::guardarTrazoActual()
{
    // No se guarda nada si no hay base o si el trazo no tiene puntos.
    if (db == nullptr) {
        return;
    }

    if (trazoActual.puntos.isEmpty()) {
        return;
    }

    int idTrazo = db->guardarTrazo(
        idUsuario,
        trazoActual.color,
        trazoActual.grosor
        );

    if (idTrazo == -1) {
        return;
    }

    for (int i = 0; i < trazoActual.puntos.size(); i++) {
        db->guardarCoordenada(
            idTrazo,
            trazoActual.puntos[i],
            i
            );
    }
}

void Pintura::cargarDesdeBase()
{
    // Reconstruye los trazos guardados para el usuario autenticado.
    if (db == nullptr) {
        return;
    }

    QVector<TrazoDB> datos = db->cargarTrazos(idUsuario);

    trazos.clear();

    for (int i = 0; i < datos.size(); i++) {

        Trazo trazo;

        trazo.color = datos[i].color;
        trazo.grosor = datos[i].grosor;
        trazo.puntos = datos[i].puntos;

        trazos.push_back(trazo);
    }

    update();
}
