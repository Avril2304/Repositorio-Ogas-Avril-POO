#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "monitorservice.h"

class QLabel;
class QPushButton;
class QLineEdit;
class QSpinBox;
class QListWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    // Slots conectados a botones y senales del servicio de monitoreo.
    void onManualRefresh();
    void onApplySettings();
    void updatePanel(const ServerHealth &health);
    void addEvent(const QString &eventText);

private:
    // Servicio que consulta el endpoint y avisa a la ventana mediante senales.
    MonitorService monitorService;

    // Controles de configuracion que el usuario puede modificar.
    QLineEdit *endpointEdit;
    QSpinBox *intervalSpin;
    QSpinBox *thresholdSpin;
    QPushButton *refreshButton;
    QPushButton *applyButton;

    // Etiquetas donde se muestran el estado general y las metricas recibidas.
    QLabel *generalStatusLabel;
    QLabel *uptimeValueLabel;
    QLabel *loadValueLabel;
    QLabel *memoryValueLabel;
    QLabel *diskValueLabel;
    QLabel *lastCheckValueLabel;

    // Lista visual con los ultimos eventos importantes del monitoreo.
    QListWidget *historyList;
};

#endif // MAINWINDOW_H
