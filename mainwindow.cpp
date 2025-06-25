#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QSvgRenderer>
#include <QFile>
#include <QDebug>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QGraphicsRectItem>
#include <QLabel>
#include "snapgraphicssvgitem.h"
#include <QtGlobal>
#include "snapgraphicssvgitem.h"
#include "zoomgraphicsview.h"     // добавьте в список include‑ов выше


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создание сцены
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600); // Ограничиваем сцену

    // Создание виджета просмотра
    // QGraphicsView *view = new QGraphicsView(scene, this);
    ZoomGraphicsView *view = new ZoomGraphicsView(scene, this);

    view->setRenderHint(QPainter::Antialiasing); // Улучшаем качество отрисовки
    setCentralWidget(view);

    // Рисуем сетку
    const int gridSize = 20;
    for (int x = 0; x <= scene->width();  x += gridSize)
        for (int y = 0; y <= scene->height(); y += gridSize)
            scene->addEllipse(x - 1, y - 1, 2, 2,
                              QPen(Qt::lightGray),
                              QBrush(Qt::lightGray));

    // Элемент для подсветки
    highlightRect = new QGraphicsRectItem();
    highlightRect->setBrush(Qt::transparent);
    highlightRect->setPen(QPen(Qt::red, 2));
    scene->addItem(highlightRect);

    // Отображение координат
    coordinatesLabel = new QLabel("Координаты: x: 0, y: 0", this);
    coordinatesLabel->setGeometry(10, 10, 200, 20);
    coordinatesLabel->show();

    // Загрузка SVG
    QString path = "X:/projects/qt_view_svg/view_svg/img/resistor.svg";
    qDebug() << "Loading SVG file:" << path;

    auto *item = new SnapGraphicsSvgItem(path, gridSize);
    item->setScale(1.0);

    // задаём начальную позицию кратно сетке, если нужно:
    auto randomX = QRandomGenerator::global()->bounded(0, 800);
    auto randomY = QRandomGenerator::global()->bounded(0, 600);

    item->setPos((randomX / gridSize) * gridSize,
                 (randomY / gridSize) * gridSize);
    scene->addItem(item);
    svgItems.append(item);

    // Загрузка SVG
    path = "X:/projects/qt_view_svg/view_svg/img/resistor1.svg";
    qDebug() << "Loading SVG file:" << path;

    auto *item2 = new SnapGraphicsSvgItem(path, gridSize);   // вместо QGraphicsSvgItem


    // задаём начальную позицию кратно сетке, если нужно:
    randomX = QRandomGenerator::global()->bounded(0, 800);
    randomY = QRandomGenerator::global()->bounded(0, 600);

    item2->setPos((randomX / gridSize) * gridSize,
                 (randomY / gridSize) * gridSize);
    scene->addItem(item2);
    svgItems.append(item2);


    // Загрузка SVG
    path = "X:/projects/qt_view_svg/view_svg/img/resistor2.svg";
    qDebug() << "Loading SVG file:" << path;

    auto *item3 = new SnapGraphicsSvgItem(path, gridSize);   // вместо QGraphicsSvgItem


    // задаём начальную позицию кратно сетке, если нужно:
    randomX = QRandomGenerator::global()->bounded(0, 800);
    randomY = QRandomGenerator::global()->bounded(0, 600);

    item3->setPos((randomX / gridSize) * gridSize,
                  (randomY / gridSize) * gridSize);
    scene->addItem(item3);
    svgItems.append(item3);

    // Загрузка SVG
    path = "X:/projects/qt_view_svg/view_svg/img/resistor3.svg";
    qDebug() << "Loading SVG file:" << path;

    // задаём начальную позицию кратно сетке, если нужно:
    auto *item4 = new SnapGraphicsSvgItem(path, gridSize);   // вместо QGraphicsSvgItem


    // задаём начальную позицию кратно сетке, если нужно:
    randomX = QRandomGenerator::global()->bounded(0, 800);
    randomY = QRandomGenerator::global()->bounded(0, 600);

    item4->setPos((randomX / gridSize) * gridSize,
                  (randomY / gridSize) * gridSize);
    scene->addItem(item4);
    svgItems.append(item4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        QGraphicsView *view = qobject_cast<QGraphicsView*>(centralWidget());
        if (!view) return;

        QPointF scenePos = view->mapToScene(event->pos());
        selectedItem = dynamic_cast<QGraphicsSvgItem*>(scene->itemAt(scenePos, view->transform()));
        if (selectedItem) {
            dragStartPos = scenePos;
            selectedItem->setCursor(Qt::ClosedHandCursor);
        }
    }
    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (selectedItem && event->buttons() & Qt::RightButton) {
        QGraphicsView *view = qobject_cast<QGraphicsView*>(centralWidget());
        if (!view) return;

        QPointF scenePos = view->mapToScene(event->pos());

        int gridSize = 20;
        qreal targetX = qRound(scenePos.x() / gridSize) * gridSize;
        qreal targetY = qRound(scenePos.y() / gridSize) * gridSize;

        // Обновляем позицию выбранного объекта
        selectedItem->setPos(targetX, targetY);

        // Обновляем подсветку
        highlightRect->setRect(targetX, targetY, gridSize, gridSize);

        // Обновляем координаты в QLabel
        coordinatesLabel->setText(QString("Координаты: x: %1, y: %2").arg(targetX).arg(targetY));
    }
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (selectedItem && event->button() == Qt::RightButton) {
        selectedItem->unsetCursor();
        selectedItem = nullptr;

        // Сбрасываем подсветку
        highlightRect->setRect(0, 0, 0, 0);
    }
    QMainWindow::mouseReleaseEvent(event);
}
