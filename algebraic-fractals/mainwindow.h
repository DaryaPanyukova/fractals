#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
 #include "complex.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void DrawArea(QRectF);
    void DrawMandelbrot(double, double, double, double);
private:
    Ui::MainWindow *ui;
   // QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
