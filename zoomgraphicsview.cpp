#include "zoomgraphicsview.h"

ZoomGraphicsView::ZoomGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    // Зум будет происходить относительно курсора
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}

void ZoomGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() == 0) {
        QGraphicsView::wheelEvent(event);
        return;
    }

    const double factorStep = 1.1;          // шаг изменения ~10 %
    double factor = 1.0;

    if (event->angleDelta().y() > 0 && zoomLevel < maxZoom) {
        factor = factorStep;                // приближаем
        ++zoomLevel;
    } else if (event->angleDelta().y() < 0 && zoomLevel > minZoom) {
        factor = 1.0 / factorStep;          // отдаляем
        --zoomLevel;
    } else {
        event->accept();
        return;                             // достигнут предел
    }

    scale(factor, factor);
    event->accept();
}
