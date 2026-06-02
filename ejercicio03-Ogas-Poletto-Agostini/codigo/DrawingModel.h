#pragma once

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QColor>
#include <QImage>
#include <QJsonObject>
#include <QJsonArray>
#include <QUuid>

// Representa un trazo individual, ya sea de lapiz o de goma.
struct Stroke {
    QString id;           // ID unico usado para mezclar estados remotos.
    QVector<QPointF> points;
    QColor color;
    int thickness;
    bool isEraser;
    qint64 timestamp;     // Orden temporal para resolver el orden de dibujo.

    Stroke() : thickness(6), isEraser(false), timestamp(0) {
        id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    }

    QJsonObject toJson() const;
    static Stroke fromJson(const QJsonObject &obj);
};

// Modelo central del dibujo: almacena trazos, serializa estado y renderiza.
class DrawingModel : public QObject {
    Q_OBJECT

public:
    explicit DrawingModel(QObject *parent = nullptr);

    // Gestion del trazo que esta siendo dibujado.
    void beginStroke(const QPointF &point, const QColor &color, int thickness, bool isEraser);
    void addPoint(const QPointF &point);
    void endStroke();

    // Mezcla incremental: agrega trazos remotos que aun no existen localmente.
    void mergeStrokes(const QVector<Stroke> &remoteStrokes);

    const QVector<Stroke> &strokes() const { return m_strokes; }
    Stroke *currentStroke() { return m_currentStroke; }

    // Serializacion para enviar/recibir el dibujo como JSON.
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &obj);

    // Renderiza todos los trazos sobre una imagen destino.
    void renderToImage(QImage &image) const;

    void clear();

signals:
    void strokeAdded(const Stroke &stroke);
    void modelChanged();

private:
    QVector<Stroke> m_strokes;
    Stroke *m_currentStroke = nullptr;

    void renderStroke(QPainter &painter, const Stroke &stroke) const;
    QVector<QPointF> catmullRomSpline(const QVector<QPointF> &pts, int segments = 8) const;
};
