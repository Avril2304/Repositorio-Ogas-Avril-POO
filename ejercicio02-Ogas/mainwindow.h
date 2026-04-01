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
    void onManualRefresh();
    void onApplySettings();
    void updatePanel(const ServerHealth &health);
    void addEvent(const QString &eventText);

private:
    MonitorService monitorService;

    QLineEdit *endpointEdit;
    QSpinBox *intervalSpin;
    QSpinBox *thresholdSpin;
    QPushButton *refreshButton;
    QPushButton *applyButton;

    QLabel *generalStatusLabel;
    QLabel *uptimeValueLabel;
    QLabel *loadValueLabel;
    QLabel *memoryValueLabel;
    QLabel *diskValueLabel;
    QLabel *lastCheckValueLabel;

    QListWidget *historyList;
};

#endif // MAINWINDOW_H