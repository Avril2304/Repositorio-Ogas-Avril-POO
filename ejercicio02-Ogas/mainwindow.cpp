#include "mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QListWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Panel de monitoreo VPS");
    resize(850, 600);

    setStyleSheet(
        "QWidget {"
        "   background-color: #111827;"
        "   color: #f9fafb;"
        "   font-family: Segoe UI;"
        "   font-size: 14px;"
        "}"
        "QGroupBox {"
        "   border: 1px solid #374151;"
        "   border-radius: 10px;"
        "   margin-top: 12px;"
        "   padding-top: 14px;"
        "   font-weight: bold;"
        "   color: #e5e7eb;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   left: 12px;"
        "   padding: 0 6px 0 6px;"
        "   color: #d1d5db;"
        "}"
        "QLineEdit, QSpinBox, QListWidget {"
        "   background-color: #1f2937;"
        "   border: 1px solid #4b5563;"
        "   border-radius: 8px;"
        "   padding: 6px;"
        "   color: #f9fafb;"
        "}"
        "QLineEdit:focus, QSpinBox:focus {"
        "   border: 1px solid #3b82f6;"
        "}"
        "QPushButton {"
        "   background-color: #2563eb;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 8px 14px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #1d4ed8;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1e40af;"
        "}"
        "QListWidget {"
        "   padding: 8px;"
        "}"
        "QListWidget::item {"
        "   padding: 6px;"
        "   margin-bottom: 4px;"
        "   border-radius: 6px;"
        "   background-color: #273244;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #374151;"
        "}"
        );

    QLabel *titleLabel = new QLabel("Monitoreo del VPS");
    QFont titleFont;
    titleFont.setPointSize(22);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #ffffff; margin-bottom: 6px;");

    endpointEdit = new QLineEdit;
    endpointEdit->setPlaceholderText("http://127.0.0.1:8000/health");
    endpointEdit->setText("http://127.0.0.1:8000/health");

    intervalSpin = new QSpinBox;
    intervalSpin->setRange(1, 3600);
    intervalSpin->setValue(10);
    intervalSpin->setSuffix(" s");

    thresholdSpin = new QSpinBox;
    thresholdSpin->setRange(1, 100);
    thresholdSpin->setValue(80);
    thresholdSpin->setSuffix(" %");

    refreshButton = new QPushButton("Refrescar ahora");
    applyButton = new QPushButton("Aplicar");

    QGroupBox *configBox = new QGroupBox("Configuración");
    QGridLayout *configLayout = new QGridLayout;

    configLayout->addWidget(new QLabel("Endpoint:"), 0, 0);
    configLayout->addWidget(endpointEdit, 0, 1, 1, 3);

    configLayout->addWidget(new QLabel("Intervalo:"), 1, 0);
    configLayout->addWidget(intervalSpin, 1, 1);

    configLayout->addWidget(new QLabel("Umbral alerta:"), 1, 2);
    configLayout->addWidget(thresholdSpin, 1, 3);

    configLayout->addWidget(refreshButton, 2, 2);
    configLayout->addWidget(applyButton, 2, 3);

    configBox->setLayout(configLayout);

    generalStatusLabel = new QLabel("DESCONOCIDO");
    generalStatusLabel->setAlignment(Qt::AlignCenter);
    generalStatusLabel->setMinimumHeight(75);
    generalStatusLabel->setStyleSheet(
        "QLabel {"
        "   background-color: #374151;"
        "   color: white;"
        "   font-size: 28px;"
        "   font-weight: bold;"
        "   border: 1px solid #4b5563;"
        "   border-radius: 12px;"
        "   padding: 12px;"
        "   letter-spacing: 1px;"
        "}"
        );

    uptimeValueLabel = new QLabel("-");
    loadValueLabel = new QLabel("-");
    memoryValueLabel = new QLabel("-");
    diskValueLabel = new QLabel("-");
    lastCheckValueLabel = new QLabel("-");

    QGroupBox *metricsBox = new QGroupBox("Métricas principales");
    QGridLayout *metricsLayout = new QGridLayout;

    metricsLayout->addWidget(new QLabel("Uptime:"), 0, 0);
    metricsLayout->addWidget(uptimeValueLabel, 0, 1);

    metricsLayout->addWidget(new QLabel("Carga:"), 1, 0);
    metricsLayout->addWidget(loadValueLabel, 1, 1);

    metricsLayout->addWidget(new QLabel("Memoria:"), 2, 0);
    metricsLayout->addWidget(memoryValueLabel, 2, 1);

    metricsLayout->addWidget(new QLabel("Disco:"), 3, 0);
    metricsLayout->addWidget(diskValueLabel, 3, 1);

    metricsLayout->addWidget(new QLabel("Último chequeo:"), 4, 0);
    metricsLayout->addWidget(lastCheckValueLabel, 4, 1);

    metricsBox->setLayout(metricsLayout);

    historyList = new QListWidget;

    QGroupBox *historyBox = new QGroupBox("Historial corto de eventos");
    QVBoxLayout *historyLayout = new QVBoxLayout;
    historyLayout->addWidget(historyList);
    historyBox->setLayout(historyLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(14, 14, 14, 14);
    mainLayout->setSpacing(14);

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(configBox);
    mainLayout->addWidget(generalStatusLabel);
    mainLayout->addWidget(metricsBox);
    mainLayout->addWidget(historyBox);

    setLayout(mainLayout);

    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::onManualRefresh);
    connect(applyButton, &QPushButton::clicked, this, &MainWindow::onApplySettings);

    connect(&monitorService, &MonitorService::healthUpdated, this, &MainWindow::updatePanel);
    connect(&monitorService, &MonitorService::newEvent, this, &MainWindow::addEvent);

    addEvent("Panel iniciado correctamente.");

    onApplySettings();
    monitorService.start();
}

void MainWindow::onManualRefresh()
{
    monitorService.checkNow();
}

void MainWindow::onApplySettings()
{
    monitorService.setEndpoint(endpointEdit->text());
    monitorService.setInterval(intervalSpin->value());
    monitorService.setThreshold(thresholdSpin->value());

    addEvent("Configuración actualizada.");
}

void MainWindow::updatePanel(const ServerHealth &health)
{
    uptimeValueLabel->setText(health.uptime);
    loadValueLabel->setText(QString::number(health.load, 'f', 2));
    memoryValueLabel->setText(QString::number(health.memory) + " %");
    diskValueLabel->setText(QString::number(health.disk) + " %");
    lastCheckValueLabel->setText(health.checkedAt);

    if (health.status == "ok") {
        generalStatusLabel->setText("OK");
        generalStatusLabel->setStyleSheet(
            "QLabel {"
            "   background-color: #14532d;"
            "   color: #f0fdf4;"
            "   font-size: 28px;"
            "   font-weight: bold;"
            "   border: 1px solid #22c55e;"
            "   border-radius: 12px;"
            "   padding: 12px;"
            "   letter-spacing: 1px;"
            "}"
            );
    } else if (health.status == "alert") {
        generalStatusLabel->setText("ALERTA");
        generalStatusLabel->setStyleSheet(
            "QLabel {"
            "   background-color: #78350f;"
            "   color: #fffbeb;"
            "   font-size: 28px;"
            "   font-weight: bold;"
            "   border: 1px solid #f59e0b;"
            "   border-radius: 12px;"
            "   padding: 12px;"
            "   letter-spacing: 1px;"
            "}"
            );
    } else {
        generalStatusLabel->setText("CAÍDO");
        generalStatusLabel->setStyleSheet(
            "QLabel {"
            "   background-color: #7f1d1d;"
            "   color: #fef2f2;"
            "   font-size: 28px;"
            "   font-weight: bold;"
            "   border: 1px solid #ef4444;"
            "   border-radius: 12px;"
            "   padding: 12px;"
            "   letter-spacing: 1px;"
            "}"
            );
    }
}

void MainWindow::addEvent(const QString &eventText)
{
    historyList->insertItem(0, eventText);

    if (historyList->count() > 8) {
        delete historyList->takeItem(historyList->count() - 1);
    }
}