#include "monitorservice.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

MonitorService::MonitorService(QObject *parent)
    : QObject(parent), intervalSec(10), threshold(80)
{
    connect(&timer, &QTimer::timeout, this, &MonitorService::checkNow);
}

void MonitorService::setEndpoint(const QString &url)
{
    endpoint = url;
}

void MonitorService::setInterval(int seconds)
{
    intervalSec = seconds;
    timer.start(intervalSec * 1000);
}

void MonitorService::setThreshold(int value)
{
    threshold = value;
}

void MonitorService::start()
{
    timer.start(intervalSec * 1000);
    checkNow();
}

void MonitorService::checkNow()
{
    if (endpoint.isEmpty()) return;

    QNetworkRequest request{QUrl(endpoint)};
    QNetworkReply *reply = manager.get(request);

    connect(reply, &QNetworkReply::finished, this, &MonitorService::onReplyFinished);
}

void MonitorService::onReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    ServerHealth health;
    health.checkedAt = QDateTime::currentDateTime().toString("hh:mm:ss");

    if (reply->error() != QNetworkReply::NoError) {
        health.status = "down";
        emit healthUpdated(health);
        emit newEvent("Servidor caído o endpoint inaccesible");
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (!doc.isObject()) {
        emit newEvent("Error parseando JSON");
        reply->deleteLater();
        return;
    }

    QJsonObject obj = doc.object();

    health.status = obj["status"].toString();
    health.uptime = obj["uptime"].toString();
    health.load = obj["load"].toDouble();
    health.memory = obj["memory"].toInt();
    health.disk = obj["disk"].toInt();

    if (health.memory > threshold || health.disk > threshold) {
        health.status = "alert";
        emit newEvent("Alerta: uso alto de recursos");
    } else {
        emit newEvent("Chequeo OK");
    }

    emit healthUpdated(health);

    reply->deleteLater();
}