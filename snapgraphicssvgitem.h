// snapgraphicssvgitem.h
#ifndef SNAPGRAPHICSSVGITEM_H
#define SNAPGRAPHICSSVGITEM_H

#include <QGraphicsSvgItem>

class SnapGraphicsSvgItem : public QGraphicsSvgItem
{
public:
    SnapGraphicsSvgItem(const QString& file, int grid, QGraphicsItem *parent = nullptr)
        : QGraphicsSvgItem(file, parent), m_grid(grid)
    {
        setFlags(ItemIsMovable            |
                 ItemIsSelectable         |
                 ItemSendsGeometryChanges);   // важно!
    }

protected:
    // перехватываем попытку изменения позиции
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value) override
    {
        if (change == ItemPositionChange && scene()) {
            const QPointF p = value.toPointF();
            const qreal x  = qRound(p.x() / m_grid) * m_grid;
            const qreal y  = qRound(p.y() / m_grid) * m_grid;
            return QPointF(x, y);               // отдаём «прищёлкнутую» точку
        }
        return QGraphicsSvgItem::itemChange(change, value);
    }

private:
    int m_grid;
};

#endif // SNAPGRAPHICSSVGITEM_H
