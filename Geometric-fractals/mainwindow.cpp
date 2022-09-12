#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
int n = 3;

QBrush blackBrush(QColor(0,0,0));
QPen blackPen(QColor(0,0,0));

QBrush whiteBrush(QColor(255,255,255));
QPen whitePen(QColor(255, 255, 255));

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    square_scene = new QGraphicsScene;
    ui->square_graphicsView->setScene(square_scene);

    triangle_scene = new QGraphicsScene;
    ui->triangle_graphicsView->setScene(triangle_scene);

    tree_scene = new QGraphicsScene;
    ui->tree_graphicsView->setScene(tree_scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::RecursiveSierpinskiSquare(double x, double y, double size, int level) {
    if (level == 0) return;
    double next_size = size / 3;
    square_scene->addRect(x + next_size, y + next_size, next_size, next_size, blackPen, blackBrush);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            RecursiveSierpinskiSquare(x + next_size * j, y + next_size * i, next_size, level-1);
        }
    }

}

void MainWindow::on_square_horizontalSlider_valueChanged(int value)
{

    square_scene->clear();
   // std::string s = std::to_string(value);

   // char const *pchar = s.c_str();
   // qWarning(pchar);
     RecursiveSierpinskiSquare(50, 50, ui->square_graphicsView->geometry().width() - 100, value);
}


void MainWindow::RecursiveSierpinskiTriangle(double xl, double yl,
                                             double xt, double yt,
                                             double xr, double yr,
                                             int level) {
    if (level == 0) return;


    double left_mid_x = (xl + xt) / 2, left_mid_y =  (yl + yt) / 2;
    double right_mid_x = (xt + xr) / 2, right_mid_y = (yt + yr) / 2;
    double bottom_mid_x = (xr + xl) / 2, bottom_mid_y =  (yl + yr) / 2;

    QPolygonF Triangle;
    Triangle.append(QPointF(left_mid_x, left_mid_y));
    Triangle.append(QPointF(right_mid_x, right_mid_y));
    Triangle.append(QPointF(bottom_mid_x, bottom_mid_y));

    triangle_scene->addPolygon(Triangle, whitePen, whiteBrush);


    RecursiveSierpinskiTriangle(left_mid_x, left_mid_y, xt, yt,
            right_mid_x, right_mid_y, level - 1);

    RecursiveSierpinskiTriangle(bottom_mid_x, bottom_mid_y, right_mid_x, right_mid_y,
            xr, yr, level - 1);

    RecursiveSierpinskiTriangle(xl, yl, left_mid_x, left_mid_y,
            bottom_mid_x, bottom_mid_y, level - 1);

}

void MainWindow::on_triangle_horizontalSlider_valueChanged(int value)
{
    triangle_scene->clear();


    int size =  ui->triangle_graphicsView->geometry().width() - 100;

    if (value >= 1) {
        QPolygonF Triangle;
        Triangle.append(QPointF(50, size + 50));
        Triangle.append(QPointF(50 + size / 2, 50));
        Triangle.append(QPointF(size + 50, size + 50));

        triangle_scene->addPolygon(Triangle, blackPen, blackBrush);

        RecursiveSierpinskiTriangle(50, size + 50, 50 + size / 2, 50, size + 50, size + 50, value - 1);
    }
}


void MainWindow::RecursiveTree(double x, double y, char side, double size, int level) {
    if (level == 0) return;

    if (side == 'l') {
         tree_scene->addLine(x, y, x - size, y);
         tree_scene->addLine(x - size, y,  x - size - size / 2, y + size / 2 );
         tree_scene->addLine(x - size, y,  x - size - size / 2, y - size / 2);

         RecursiveTree(x - size - size / 2, y + size / 2, 'l', size/2, level-1);
         RecursiveTree(x - size - size / 2, y - size / 2, 'l', size/2, level-1);

         RecursiveTree(x - size - size / 2, y + size / 2, 'd', size/2, level-1);
         RecursiveTree(x - size - size / 2, y - size / 2, 'u', size/2, level-1);

    } else if (side == 'r') {
        tree_scene->addLine(x, y, x + size, y);
        tree_scene->addLine(x + size, y,  x + size + size / 2, y + size / 2 );
        tree_scene->addLine(x + size, y,  x + size + size / 2, y - size / 2);

        RecursiveTree(x + size + size / 2, y + size / 2, 'r', size/2, level-1);
        RecursiveTree(x + size + size / 2, y - size / 2, 'r', size/2, level-1);


        RecursiveTree(x + size + size / 2, y + size / 2, 'd', size/2, level-1);
        RecursiveTree(x + size + size / 2, y - size / 2, 'u', size/2, level-1);

    } else if (side == 'u') {
        tree_scene->addLine(x, y, x, y - size);
        tree_scene->addLine(x, y - size,  x - size / 2, y - size - size / 2 );
        tree_scene->addLine(x, y - size,  x + size / 2, y - size - size / 2 );

        RecursiveTree(x - size / 2, y - size - size / 2, 'l', size/2, level-1);
        RecursiveTree(x - size / 2, y - size - size / 2, 'u', size/2, level-1);

        RecursiveTree(x + size / 2, y - size - size / 2, 'r', size/2, level-1);
        RecursiveTree(x + size / 2, y - size - size / 2, 'u', size/2, level-1);

    } else {
        tree_scene->addLine(x, y, x, y + size);
        tree_scene->addLine(x, y + size,  x - size / 2, y + size + size / 2 );
        tree_scene->addLine(x, y + size,  x + size / 2, y + size + size / 2 );


        RecursiveTree(x - size / 2, y + size + size / 2 , 'l', size/2, level-1);
        RecursiveTree(x - size / 2, y + size + size / 2 , 'd', size/2, level-1);

        RecursiveTree(x + size / 2, y + size + size / 2 , 'r', size/2, level-1);
        RecursiveTree(x + size / 2, y + size + size / 2 , 'd', size/2, level-1);
    }
}


void MainWindow::on_tree_horizontalSlider_valueChanged(int value)
{
    tree_scene->clear();
    int size =  ui->triangle_graphicsView->geometry().width();

    double trunk_size = 200;
    double branch_size = trunk_size / 2;

    tree_scene->addLine(size/2, size, size/2, size - trunk_size);
    tree_scene->addLine(size/2, size - trunk_size, size/2 - branch_size, size - trunk_size - branch_size);
    tree_scene->addLine(size/2, size - trunk_size, size/2 + branch_size, size - trunk_size - branch_size);


    RecursiveTree(size/2 - branch_size, size - trunk_size - branch_size, 'l', branch_size, value - 1 );
    RecursiveTree(size/2 + branch_size, size - trunk_size - branch_size, 'r', branch_size, value - 1 );


    RecursiveTree(size/2 - branch_size, size - trunk_size - branch_size, 'u', branch_size, value - 1 );
    RecursiveTree(size/2 + branch_size, size - trunk_size - branch_size, 'u', branch_size, value - 1 );


}
