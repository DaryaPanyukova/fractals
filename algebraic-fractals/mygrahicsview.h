#ifndef MYGRAHICSVIEW_H
#define MYGRAHICSVIEW_H

#include <QGraphicsView>

#include <QObject>

#include <QWidget>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsItem>

class myGrahicsView : public QGraphicsView
{
    Q_OBJECT

public:
    myGrahicsView(QWidget* parent = 0);
    QGraphicsScene *scene;
    QGraphicsRectItem *itm;
    QImage* image;
    double scale;
    double cur_x, cur_y;

signals:
    void signal(QRectF);
    void signal_redraw(double, double, double, double);

private:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

protected:
    double x_pressed, y_pressed;
    long double pressed_;

};

#endif // MYGRAHICSVIEW_H
