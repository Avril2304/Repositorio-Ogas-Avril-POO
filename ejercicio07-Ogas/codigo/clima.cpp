#include "clima.h"

#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Clima::Clima(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(procesarRespuesta(QNetworkReply*)));
}

void Clima::consultarClima(QString ciudad, QString apiKey)
{
    QString url = "https://api.openweathermap.org/data/2.5/weather?q="
                  + ciudad +
                  "&units=metric&appid=" + apiKey;

    QNetworkRequest request((QUrl(url)));

    manager->get(request);
}

void Clima::procesarRespuesta(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        emit climaActualizado("20 °C", "modo offline - clima simulado");
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    if (!obj.contains("main") || !obj.contains("weather")) {
        emit climaActualizado("20 °C", "modo offline - datos inválidos");
        reply->deleteLater();
        return;
    }

    double temp = obj["main"].toObject()["temp"].toDouble();
    QString descripcion = obj["weather"].toArray()[0].toObject()["description"].toString();

    emit climaActualizado(QString::number(temp) + " °C", descripcion);

    reply->deleteLater();
}