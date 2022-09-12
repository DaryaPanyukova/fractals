#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>
#include <QLabel>
#include <random>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    void drawPixel(double, double, QColor);

    void RecursiveFillRect(QImage&, double, double, double,
                                       QColor, QColor, QColor, QColor);


    /*void RecursiveFillRect(QImage&,int, int, int, int,
                                         QColor, QColor, QColor, QColor);*/
};
#endif // MAINWINDOW_H
