#pragma once
#include <QGraphicsView>
#include <QWheelEvent>

class ZoomGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ZoomGraphicsView(QGraphicsScene *scene,
                              QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    int  zoomLevel = 0;     // текущий «шаг» масштаба
    const int maxZoom = 20; // максимум +20 шагов
    const int minZoom = -10;// минимум ‑10 шагов
};
