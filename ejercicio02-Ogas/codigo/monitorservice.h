#ifndef MONITORSERVICE_H
#define MONITORSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QString>

// Estructura simple con los datos que la interfaz necesita mostrar.
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

    // Configuracion editable desde la ventana principal.
    void setEndpoint(const QString &url);
    void setInterval(int seconds);
    void setThreshold(int value);

public slots:
    // start() inicia el monitoreo periodico; checkNow() hace una consulta puntual.
    void start();
    void checkNow();

signals:
    // Senales usadas para desacoplar el servicio de la interfaz grafica.
    void healthUpdated(const ServerHealth &health);
    void newEvent(const QString &event);

private slots:
    // Procesa la respuesta HTTP cuando QNetworkReply informa que termino.
    void onReplyFinished();

private:
    // Objetos de Qt usados para red y ejecucion periodica.
    QNetworkAccessManager manager;
    QTimer timer;

    // Parametros actuales del monitoreo.
    QString endpoint;
    int intervalSec;
    int threshold;
};

#endif // MONITORSERVICE_H
