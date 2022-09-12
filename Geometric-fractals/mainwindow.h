#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGraphicsScene"
#include <QVector>

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

    void on_square_horizontalSlider_valueChanged(int value);

    void on_triangle_horizontalSlider_valueChanged(int value);

    void on_tree_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *square_scene;
    QGraphicsScene *triangle_scene;
    QGraphicsScene *tree_scene;


    void RecursiveSierpinskiSquare(double, double, double, int);

    void RecursiveSierpinskiTriangle(double, double, double,
                                             double, double, double, int);

    void RecursiveTree(double, double, char, double, int);
};

#endif // MAINWINDOW_H
