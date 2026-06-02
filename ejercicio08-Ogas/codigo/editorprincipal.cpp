#include "editorprincipal.h"

#include "validadorcpp.h"
#include "validadorpython.h"
#include "validadorjava.h"
#include "logmanager.h"
#include "configmanager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <QTextBlock>
#include <QPixmap>
#include <QPainter>
#include <QFileDialog>
#include <QDateTime>

EditorPrincipal::EditorPrincipal(QWidget *parent)
    : Pantalla(parent)
{
    validadorActual = nullptr;
    lineaActual = 0;

    inicializarUI();
    conectarEventos();
    cargarDatos();
    cambiarValidador();
}

EditorPrincipal::~EditorPrincipal()
{
    delete validadorActual;
}

void EditorPrincipal::inicializarUI()
{
    setWindowTitle("Ejercicio 08 - Editor Multilenguaje");

    // Panel izquierdo: selector de lenguaje, editor y acciones principales.
    comboLenguaje = new QComboBox(this);
    comboLenguaje->addItem("C++");
    comboLenguaje->addItem("Python");
    comboLenguaje->addItem("Java");

    editorCodigo = new QTextEdit(this);
    editorCodigo->setPlaceholderText("Escriba su código aquí...");

    lblMensaje = new QLabel("Seleccione un lenguaje y escriba código.", this);

    btnExportar = new QPushButton("Exportar a JPG", this);
    btnSalir = new QPushButton("Salir", this);

    QVBoxLayout *layoutEditor = new QVBoxLayout();
    layoutEditor->addWidget(comboLenguaje);
    layoutEditor->addWidget(editorCodigo);
    layoutEditor->addWidget(lblMensaje);
    layoutEditor->addWidget(btnExportar);
    layoutEditor->addWidget(btnSalir);

    // Panel derecho: datos personales con estilo de perfil profesional.
    QLabel *lblFoto = new QLabel("AO", this);
    lblFoto->setFixedSize(120, 120);
    lblFoto->setAlignment(Qt::AlignCenter);
    lblFoto->setStyleSheet(
        "background-color: #0A66C2;"
        "color: white;"
        "border-radius: 60px;"
        "font-size: 32px;"
        "font-weight: bold;"
        );

    QLabel *lblNombre = new QLabel("Avril Ogas", this);
    lblNombre->setAlignment(Qt::AlignCenter);
    lblNombre->setStyleSheet(
        "font-size: 22px;"
        "font-weight: bold;"
        "color: #1f1f1f;"
        );

    QLabel *lblTitulo = new QLabel("Estudiante de Ingeniería en Informática", this);
    lblTitulo->setAlignment(Qt::AlignCenter);
    lblTitulo->setWordWrap(true);
    lblTitulo->setStyleSheet(
        "font-size: 13px;"
        "color: #555555;"
        );

    QLabel *lblDescripcion = new QLabel(
        "Perfil orientado al desarrollo de software, programación en C++ "
        "y manejo de bases de datos. Interés en crear aplicaciones claras, "
        "funcionales y bien organizadas.",
        this
        );
    lblDescripcion->setWordWrap(true);
    lblDescripcion->setStyleSheet(
        "font-size: 13px;"
        "color: #333333;"
        );

    QLabel *lblHabilidades = new QLabel(
        "<b>Habilidades</b><br>"
        "• C++ y POO<br>"
        "• Qt Widgets<br>"
        "• MySQL / SQLite<br>"
        "• Git y GitHub<br>"
        "• Resolución de problemas",
        this
        );
    lblHabilidades->setWordWrap(true);
    lblHabilidades->setStyleSheet(
        "font-size: 13px;"
        "color: #333333;"
        );

    QLabel *lblContacto = new QLabel(
        "<b>Contacto</b><br>"
        "GitHub: Avril2304<br>"
        "LinkedIn: Perfil profesional<br>"
        "Córdoba, Argentina",
        this
        );
    lblContacto->setWordWrap(true);
    lblContacto->setStyleSheet(
        "font-size: 13px;"
        "color: #333333;"
        );

    QWidget *panelCV = new QWidget(this);
    panelCV->setFixedWidth(320);
    panelCV->setStyleSheet(
        "background-color: #F3F2EF;"
        "border-left: 1px solid #d0d0d0;"
        );

    QVBoxLayout *layoutCV = new QVBoxLayout(panelCV);
    layoutCV->setContentsMargins(25, 25, 25, 25);
    layoutCV->setSpacing(14);

    layoutCV->addWidget(lblFoto, 0, Qt::AlignCenter);
    layoutCV->addWidget(lblNombre);
    layoutCV->addWidget(lblTitulo);
    layoutCV->addSpacing(10);
    layoutCV->addWidget(lblDescripcion);
    layoutCV->addSpacing(10);
    layoutCV->addWidget(lblHabilidades);
    layoutCV->addSpacing(10);
    layoutCV->addWidget(lblContacto);
    layoutCV->addStretch();

    panelCV->setLayout(layoutCV);


    QHBoxLayout *layoutPrincipal = new QHBoxLayout(this);
    layoutPrincipal->addLayout(layoutEditor);
    layoutPrincipal->addWidget(panelCV);

    setLayout(layoutPrincipal);
}

void EditorPrincipal::conectarEventos()
{
    // El cambio de lenguaje reemplaza el validador activo.
    connect(comboLenguaje, SIGNAL(currentIndexChanged(int)),
            this, SLOT(cambiarValidador()));

    //connect(editorCodigo, SIGNAL(textChanged()),
    //        this, SLOT(validarCodigoActual()));
    connect(editorCodigo, SIGNAL(cursorPositionChanged()),
            this, SLOT(validarLineaAbandonada()));

    connect(btnExportar, &QPushButton::clicked,
            this, &EditorPrincipal::exportarCodigoJPG);

    connect(btnSalir, &QPushButton::clicked,
            this, &EditorPrincipal::close);

    registrarEvento("Eventos conectados");
}

void EditorPrincipal::cargarDatos()
{
    // Lee lenguaje por defecto y ruta de exportacion desde configuracion.
    QString lenguajeDefecto = ConfigManager::obtenerValor("lenguaje_defecto", "C++");

    int indice = comboLenguaje->findText(lenguajeDefecto);

    if (indice >= 0) {
        comboLenguaje->setCurrentIndex(indice);
    }

    rutaExportacion = ConfigManager::obtenerValor("ruta_exportacion",
                                                  "datos/codigo_exportado.jpg");

    registrarEvento("Datos del editor cargados desde archivo de configuración");
}

bool EditorPrincipal::validarEstado()
{
    return !editorCodigo->toPlainText().isEmpty();
}

void EditorPrincipal::cambiarValidador()
{
    // Se elimina el validador anterior para evitar memoria sin liberar.
    delete validadorActual;
    validadorActual = nullptr;

    QString lenguaje = comboLenguaje->currentText();

    if (lenguaje == "C++") {
        validadorActual = new ValidadorCpp();
    } else if (lenguaje == "Python") {
        validadorActual = new ValidadorPython();
    } else if (lenguaje == "Java") {
        validadorActual = new ValidadorJava();
    }

    lblMensaje->setText("Validador activo: " + lenguaje);
    registrarEvento("Cambio de lenguaje a " + lenguaje);

    validarCodigoActual();
}

void EditorPrincipal::validarCodigoActual()
{
    if (validadorActual == nullptr) {
        return;
    }

    // Antes de validar se quita cualquier resaltado previo.
    limpiarResaltado();

    QString codigo = editorCodigo->toPlainText();
    QStringList lineas = codigo.split('\n');

    for (int i = 0; i < lineas.size(); i++) {
        QString mensajeError;

        if (!validadorActual->validarLinea(lineas[i], mensajeError)) {

            int numeroLinea = i + 1;

            // La validacion se detiene en el primer error encontrado.
            resaltarLineaError(numeroLinea);

            lblMensaje->setText("Línea "
                                + QString::number(numeroLinea)
                                + ": "
                                + mensajeError);

            lblMensaje->setStyleSheet("color: red; font-weight: bold;");

            registrarEvento("Error de sintaxis en línea "
                            + QString::number(numeroLinea));

            return;
        }
    }

    lblMensaje->setText("Código válido para " + comboLenguaje->currentText());
    lblMensaje->setStyleSheet("color: green; font-weight: bold;");
}

void EditorPrincipal::registrarEvento(const QString &descripcion)
{
    qDebug() << "LOG:" << descripcion;
    LogManager::registrar("EditorPrincipal: " + descripcion);
}

void EditorPrincipal::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();
    }

    QWidget::keyPressEvent(event);
}

void EditorPrincipal::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton respuesta;

    respuesta = QMessageBox::question(this,
                                      "Salir",
                                      "¿Desea cerrar el editor?",
                                      QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::Yes) {
        registrarEvento("Editor cerrado");
        event->accept();
    } else {
        event->ignore();
    }
}

void EditorPrincipal::limpiarResaltado()
{
    // Se bloquean senales para que el cambio de formato no dispare validaciones.
    editorCodigo->blockSignals(true);

    QTextCursor cursor(editorCodigo->document());

    QTextCharFormat formatoNormal;
    formatoNormal.setBackground(Qt::transparent);
    formatoNormal.setForeground(Qt::black);

    cursor.select(QTextCursor::Document);
    cursor.mergeCharFormat(formatoNormal);

    editorCodigo->blockSignals(false);
}

void EditorPrincipal::resaltarLineaError(int numeroLinea)
{
    // Busca el bloque de texto y aplica un formato rojo a la linea completa.
    editorCodigo->blockSignals(true);

    QTextBlock bloque = editorCodigo->document()->findBlockByNumber(numeroLinea - 1);

    if (!bloque.isValid()) {
        editorCodigo->blockSignals(false);
        return;
    }

    QTextCursor cursor(bloque);

    QTextCharFormat formatoError;
    formatoError.setBackground(Qt::red);
    formatoError.setForeground(Qt::white);

    cursor.select(QTextCursor::LineUnderCursor);
    cursor.mergeCharFormat(formatoError);

    editorCodigo->blockSignals(false);
}

void EditorPrincipal::validarLineaAbandonada()
{
    if (validadorActual == nullptr) {
        return;
    }

    int nuevaLinea = editorCodigo->textCursor().blockNumber();

    // Solo valida cuando el cursor abandona la linea anterior.
    if (nuevaLinea == lineaActual) {
        return;
    }

    lineaActual = nuevaLinea;

    validarCodigoActual();
}

void EditorPrincipal::exportarCodigoJPG()
{
    // Convierte el texto del editor en una imagen con numeracion de lineas.
    QString codigo = editorCodigo->toPlainText();

    if (codigo.trimmed().isEmpty()) {
        QMessageBox::warning(this,
                             "Exportar",
                             "No hay código para exportar.");
        return;
    }

    QFont fuente("Courier New", 12);
    QFontMetrics metricas(fuente);

    QStringList lineas = codigo.split('\n');

    int ancho = 1000;
    int altoLinea = metricas.height() + 6;
    int alto = 60 + lineas.size() * altoLinea;

    if (alto < 400) {
        alto = 400;
    }

    QPixmap imagen(ancho, alto);
    imagen.fill(Qt::white);

    QPainter painter(&imagen);
    painter.setFont(fuente);
    painter.setPen(Qt::black);

    int y = 40;

    painter.drawText(30, y, "Código exportado - " + comboLenguaje->currentText());
    y += 30;

    for (int i = 0; i < lineas.size(); i++) {
        // Se dibuja cada linea con su numero para que la exportacion sea legible.
        QString numero = QString::number(i + 1).rightJustified(3, ' ');
        QString texto = numero + " | " + lineas[i];

        painter.drawText(30, y, texto);
        y += altoLinea;
    }

    painter.end();

    if (imagen.save(rutaExportacion, "JPG")) {
        QMessageBox::information(this,
                                 "Exportar",
                                 "El código se exportó correctamente en:\n"
                                     + rutaExportacion);

        registrarEvento("Código exportado a JPG en " + rutaExportacion);
    } else {
        QMessageBox::critical(this,
                              "Exportar",
                              "No se pudo exportar el archivo JPG.");
    }
}

void EditorPrincipal::mousePressEvent(QMouseEvent *event)
{
    registrarEvento("Click dentro del editor principal");

    QWidget::mousePressEvent(event);
}

void EditorPrincipal::resizeEvent(QResizeEvent *event)
{
    registrarEvento("Editor redimensionado");

    QWidget::resizeEvent(event);
}

void EditorPrincipal::focusInEvent(QFocusEvent *event)
{
    registrarEvento("Editor recibió foco");

    QWidget::focusInEvent(event);
}

void EditorPrincipal::focusOutEvent(QFocusEvent *event)
{
    registrarEvento("Editor perdió foco");

    validarCodigoActual();

    QWidget::focusOutEvent(event);
}
