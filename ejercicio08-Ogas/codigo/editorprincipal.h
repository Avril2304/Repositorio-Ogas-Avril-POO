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
    void cambiarValidador();
    void validarCodigoActual();
    void validarLineaAbandonada();
    void exportarCodigoJPG();

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

    ValidadorSintaxis *validadorActual;

    int lineaActual;
    void limpiarResaltado();
    void resaltarLineaError(int numeroLinea);
};

#endif // EDITORPRINCIPAL_H