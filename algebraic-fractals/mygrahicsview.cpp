#include "mygrahicsview.h"

myGrahicsView::myGrahicsView(QWidget* parent) : QGraphicsView(parent), itm(nullptr), scale(1), cur_x(0), cur_y(0) {}

void myGrahicsView::mousePressEvent(QMouseEvent *event) {
    pressed_ = true;
    this->x_pressed = event->x();
    this->y_pressed = event->y();
}

void myGrahicsView::mouseReleaseEvent(QMouseEvent *event) {

    if (!pressed_) return;
    pressed_ = false;

    if (itm != nullptr) {
        scene->removeItem(itm);
        itm = nullptr;
    }
    double mWidth = this->geometry().width();
    double mHeight = this -> geometry().height();

    if (x_pressed < event->x() && y_pressed < event->y()) {
        emit signal_redraw(x_pressed / scale, y_pressed / scale, event->x() / scale, event->y() / scale);
        cur_x += x_pressed / scale;
        cur_y += y_pressed / scale;
        double w =  (event->x() - x_pressed) / scale;
        double h =  (event->y() - y_pressed) / scale;
        scale = std::min(this->geometry().width() / w, this->geometry().height() / h);
    } else {
        if (scale <= 1.1) return;
        double w =  mWidth / scale;
        double h =  mHeight / scale;

        emit signal_redraw(-w / 2, -h / 2, 3 * w / 2, 3 * h / 2);

        cur_x = std::max(cur_x - w / 2, 0.0);
        cur_y = std::max(cur_y - h / 2, 0.0);

        scale = std::max(scale / 2, 1.0);
    }
}

void myGrahicsView::mouseMoveEvent(QMouseEvent *event) {
    if (!pressed_) return;

    if (itm != nullptr) {
        scene->removeItem(itm);
        itm = nullptr;
    }

    if (x_pressed < event->x() && y_pressed < event->y()) {
        emit signal(QRectF(x_pressed, y_pressed, event->x() -  x_pressed, event->y() - y_pressed));
    } else {
        emit signal(QRectF(event->x(),  event->y(),  x_pressed - event->x(), y_pressed - event->y()));
    }
}
