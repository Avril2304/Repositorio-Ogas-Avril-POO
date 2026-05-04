#ifndef CLIMA_H
#define CLIMA_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Clima : public QObject
{
    Q_OBJECT

public:
    explicit Clima(QObject *parent = nullptr);

    void consultarClima(QString ciudad, QString apiKey);

signals:
    void climaActualizado(QString temperatura, QString descripcion);
    void errorClima(QString mensaje);

private slots:
    void procesarRespuesta(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
};

#endif