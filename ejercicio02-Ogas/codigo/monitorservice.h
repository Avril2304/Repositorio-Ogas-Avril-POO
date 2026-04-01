#ifndef MONITORSERVICE_H
#define MONITORSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QString>

struct ServerHealth {
    QString status;
    QString uptime;
    double load;
    int memory;
    int disk;
    QString checkedAt;
};

class MonitorService : public QObject
{
    Q_OBJECT

public:
    explicit MonitorService(QObject *parent = nullptr);

    void setEndpoint(const QString &url);
    void setInterval(int seconds);
    void setThreshold(int value);

public slots:
    void start();
    void checkNow();

signals:
    void healthUpdated(const ServerHealth &health);
    void newEvent(const QString &event);

private slots:
    void onReplyFinished();

private:
    QNetworkAccessManager manager;
    QTimer timer;
    QString endpoint;
    int intervalSec;
    int threshold;
};

#endif // MONITORSERVICE_H