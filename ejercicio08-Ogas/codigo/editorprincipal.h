#ifndef EDITORPRINCIPAL_H
#define EDITORPRINCIPAL_H

#include "pantalla.h"
#include "validadorsintaxis.h"

#include <QTextEdit>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QFocusEvent>

// Editor multilenguaje con validacion, resaltado y exportacion a imagen.
class EditorPrincipal : public Pantalla
{
    Q_OBJECT

public:
    explicit EditorPrincipal(QWidget *parent = nullptr);
    ~EditorPrincipal();

    void inicializarUI() override;
    void conectarEventos() override;
    void cargarDatos() override;
    bool validarEstado() override;
    void registrarEvento(const QString &descripcion) override;

private slots:
    void cambiarValidador();       // Cambia la estrategia de validacion segun el combo.
    void validarCodigoActual();    // Recorre el texto y marca la primera linea invalida.
    void validarLineaAbandonada(); // Valida cuando el cursor pasa a otra linea.
    void exportarCodigoJPG();      // Genera una imagen JPG con el codigo escrito.

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    QTextEdit *editorCodigo;
    QComboBox *comboLenguaje;
    QLabel *lblMensaje;
    QPushButton *btnExportar;
    QPushButton *btnSalir;
    QString rutaExportacion;

    // Validador polimorfico usado por el lenguaje seleccionado.
    ValidadorSintaxis *validadorActual;

    int lineaActual;
    void limpiarResaltado();
    void resaltarLineaError(int numeroLinea);
};

#endif // EDITORPRINCIPAL_H
