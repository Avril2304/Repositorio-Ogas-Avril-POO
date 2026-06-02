#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

// Ventana principal del tablero Kanban conectado al servidor.
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void solicitarDatos();              // Pide el JSON actualizado al servidor.
    void procesarRespuesta(QNetworkReply *reply); // Reconstruye el tablero con los datos recibidos.

private:
    // --- ESTA ES LA LÍNEA QUE TE FALTABA ---
    void enviarOrden(QString urlStr);   // Envia acciones al servidor: crear, mover o borrar tarjetas.
    // ---------------------------------------

    // Objetos compartidos para red, refresco automatico y layout del tablero.
    QNetworkAccessManager *manager;
    QTimer *timer;
    QWidget *centralWidget;
    QHBoxLayout *layoutTablero;
};

#endif // MAINWINDOW_H
