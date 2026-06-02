#pragma once

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QTimer>
#include "DrawingModel.h"

// Widget encargado de mostrar el lienzo y transformar eventos del mouse
// en trazos dentro del modelo.
class CanvasView : public QWidget {
    Q_OBJECT

public:
    explicit CanvasView(DrawingModel *model, QWidget *parent = nullptr);

    void setColor(const QColor &color);
    void setThickness(int t);
    int  thickness() const { return m_thickness; }

    // Carga una imagen remota como base visual del lienzo.
    void loadImage(const QImage &img);
    QImage currentImage() const { return m_canvasImage; }

    // Reconstruye la imagen visible desde los trazos guardados en el modelo.
    void rebuildCanvas();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:
    void strokeFinished();
    void thicknessChanged(int t);

private:
    DrawingModel *m_model;

    QImage m_canvasImage;     // Trazos ya terminados.
    QImage m_overlayImage;    // Trazo actual, todavia no confirmado.

    QColor m_color;
    int    m_thickness = 6;
    bool   m_drawing   = false;
    bool   m_erasing   = false;

    // Palette: 9 colors interpolated between (192,19,76) → (24,233,199)
    QColor colorForIndex(int idx) const;   // idx 0..8

    void drawCurrentStrokeToOverlay();
    void bakeCurrentStroke();
    void initCanvas();
};
