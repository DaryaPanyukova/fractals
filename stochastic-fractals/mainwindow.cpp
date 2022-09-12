#include "mainwindow.h"
#include "ui_mainwindow.h"

QColor black(Qt::black);
QColor red(Qt::red);
QColor yellow(Qt::yellow);
QColor blue(Qt::blue);
QColor green(Qt::green);


const double RANDOM = 0.6;

std::random_device rd;
 std::mt19937 rng(rd());




double Color(int col, int size){

    int left = std::max(0.0, col - RANDOM * size);
    int right = std::min(254.0, col + RANDOM * size);

    std::uniform_int_distribution<int> uni(left, right);


    double random =  uni(rng);
    return random;
}
void MainWindow::RecursiveFillRect(QImage &image, double x, double y, double size,
                                   QColor colorLU, QColor colorRU, QColor colorRD, QColor colorLD) {

    if (size <= 1)
        return;


    int rLU = colorLU.red(), gLU = colorLU.green(), bLU = colorLU.blue();
    int rRU = colorRU.red(), gRU = colorRU.green(), bRU = colorRU.blue();
    int rLD = colorLD.red(), gLD = colorLD.green(), bLD = colorLD.blue();
    int rRD = colorRD.red(), gRD = colorRD.green(), bRD = colorRD.blue();


    int rC = Color((rLU + rRU + rLD + rRD) / 4, size); // +rand
    int gC = Color((gLU + gRU + gLD + gRD) / 4, size); //+ random_integer_g;
    int bC = Color((bLU + bRU + bLD + bRD) / 4, size); //+ random_integer_b;
    QColor colorC(rC, gC, bC);
    if (image.pixelColor(x + size / 2, y + size / 2) == QColor(255, 255, 255))
        image.setPixelColor(x + size / 2, y + size / 2, colorC);
    else {
        colorC = image.pixelColor(x + size / 2, y + size / 2);
        rC = colorC.red();
        bC = colorC.blue();
        gC = colorC.green();
    }


    int rU = Color((rLU + rRU + rC) / 3, size);
    int gU = Color((gLU + gRU + gC) / 3, size);
    int bU = Color((bLU + bRU + bC) / 3, size);
    QColor colorU(rU, gU, bU);
    if (image.pixelColor(x + size / 2, y) == QColor(255, 255, 255))
        image.setPixelColor(x + size / 2, y, colorU);
    else
        colorU = image.pixelColor(x + size / 2, y);

    int rR = Color((rRU + rRD + rC) / 3, size);
    int gR = Color((gRU + gRD + gC) / 3, size);
    int bR = Color((bRU + bRD + bC) / 3, size);
    QColor colorR(rR, gR, bR);
    if (image.pixelColor(x + size, y + size / 2) == QColor(255, 255, 255))
        image.setPixelColor(x + size, y + size / 2, colorR);
    else
        colorR = image.pixelColor(x + size, y + size / 2);


    int rD = Color((rLD + rRD + rC) / 3, size);
    int gD = Color((gLD + gRD + gC) / 3, size);
    int bD = Color((bLD + bRD + bC) / 3, size);
    QColor colorD(rD, gD, bD);
    if (image.pixelColor(x + size / 2, y + size) == QColor(255, 255, 255))
        image.setPixelColor(x + size / 2, y + size, colorD);
    else
        colorD = image.pixelColor(x + size / 2, y + size);


    int rL = Color((rLD + rLU + rC) / 3, size);
    int gL = Color((gLD + gLU + gC) / 3, size);
    int bL = Color((bLD + bLU + bC) / 3, size);
    QColor colorL(rL, gL, bL);
    if (image.pixelColor(x, y + size / 2) == QColor(255, 255, 255))
        image.setPixelColor(x, y + size / 2, colorL);
    else
        colorL = image.pixelColor(x, y + size / 2);


    RecursiveFillRect(image, x, y, size/2, colorLU, colorU, colorC, colorL);
    RecursiveFillRect(image, x + size / 2, y, size/2, colorU, colorRU, colorR, colorC);

    RecursiveFillRect(image, x, y + size /2, size/2, colorL, colorC, colorD, colorLD);
    RecursiveFillRect(image, x + size / 2, y + size / 2, size/2, colorC, colorR, colorRD, colorD);

}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);



    int size = ui->graphicsView->geometry().height() - 25;
   // int Height = ui->graphicsView->geometry().height() - 50;


    QImage image(size, size, QImage::Format_RGB32);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            image.setPixelColor(i, j, QColor(255, 255, 255));
        }
    }

    size -= 3;

    int rLU = Color((150) / 3, size);
    int gLU = Color((100) / 3, size);
    int bLU = Color((89) / 3, size);
    QColor colorLU(rLU, gLU, bLU);

    int rRU = Color((150) / 3, size);
    int gRU = Color((100) / 3, size);
    int bRU = Color((89) / 3, size);
    QColor colorRU(rRU, gRU, bRU);

    int rLD = Color((150) / 3, size);
    int gLD = Color((100) / 3, size);
    int bLD = Color((89) / 3, size);
    QColor colorLD(rLD, gLD, bLD);

    int rRD = Color((150) / 3, size);
    int gRD = Color((100) / 3, size);
    int bRD = Color((89) / 3, size);
    QColor colorRD(rRD, gRD, bRD);


    image.setPixelColor(0, 0, blue);
    image.setPixelColor(size, 0, blue);
    image.setPixelColor(0, size, blue);
    image.setPixelColor(size, size, blue);

    RecursiveFillRect(image, 0, 0, size, colorLU, colorRU, colorRD, colorLD);

    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

