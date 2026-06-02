#include "monitorservice.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

MonitorService::MonitorService(QObject *parent)
    : QObject(parent), intervalSec(10), threshold(80)
{
    // Cada vencimiento del timer dispara una nueva consulta al endpoint.
    connect(&timer, &QTimer::timeout, this, &MonitorService::checkNow);
}

void MonitorService::setEndpoint(const QString &url)
{
    endpoint = url;
}

void MonitorService::setInterval(int seconds)
{
    intervalSec = seconds;
    // Reinicia el timer para que el nuevo intervalo tenga efecto de inmediato.
    timer.start(intervalSec * 1000);
}

void MonitorService::setThreshold(int value)
{
    threshold = value;
}

void MonitorService::start()
{
    // Arranca el timer y hace un primer chequeo sin esperar el intervalo.
    timer.start(intervalSec * 1000);
    checkNow();
}

void MonitorService::checkNow()
{
    if (endpoint.isEmpty()) return;

    // QNetworkAccessManager trabaja asincronicamente: la respuesta llega luego.
    QNetworkRequest request{QUrl(endpoint)};
    QNetworkReply *reply = manager.get(request);

    // Cuando esta respuesta puntual termina, se procesa en onReplyFinished().
    connect(reply, &QNetworkReply::finished, this, &MonitorService::onReplyFinished);
}

void MonitorService::onReplyFinished()
{
    // sender() permite recuperar el QNetworkReply que emitio la senal finished().
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    ServerHealth health;
    health.checkedAt = QDateTime::currentDateTime().toString("hh:mm:ss");

    // Si hubo error de red, se marca el servidor como caido y se avisa a la UI.
    if (reply->error() != QNetworkReply::NoError) {
        health.status = "down";
        emit healthUpdated(health);
        emit newEvent("Servidor caído o endpoint inaccesible");
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    // El endpoint debe devolver un objeto JSON con las metricas esperadas.
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

    // Aunque el endpoint diga "ok", recursos altos cambian el estado a alerta.
    if (health.memory > threshold || health.disk > threshold) {
        health.status = "alert";
        emit newEvent("Alerta: uso alto de recursos");
    } else {
        emit newEvent("Chequeo OK");
    }

    emit healthUpdated(health);

    // Libera la respuesta cuando Qt vuelva al loop de eventos.
    reply->deleteLater();
}
