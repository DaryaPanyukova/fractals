#include "mainwindow.h"
#include "ui_mainwindow.h"

QBrush brush(QColor(0, 0, 255, 20));
QPen pen(QColor(0,0,0));
QColor black(Qt::black);

void MainWindow::DrawArea(QRectF rect) {
   ui->graphicsView->itm = ui->graphicsView->scene->addRect(rect, pen, brush);
}

void MainWindow::DrawMandelbrot(double xL, double yL, double xR, double yR) {

    // на какой итерации улетает в беск, в такой цвет раскр

    xL +=  ui->graphicsView->cur_x, xR += ui->graphicsView->cur_x;
    yL +=  ui->graphicsView->cur_y, yR += ui->graphicsView->cur_y;

    xL = std::max(0.0, xL),  yL = std::max(0.0, yL);
    xR = std::max(0.0, xR),  yR = std::max(0.0, yR);


    double width = xR - xL, height = yR - yL;
    double scale =  std::min(ui->graphicsView->geometry().width() / width, ui->graphicsView->geometry().height() / height);

    for (int i = 0; i < ui->graphicsView->geometry().width(); ++i) {
        for (int j = 0; j < ui->graphicsView->geometry().height(); ++j) {
             ui->graphicsView->image->setPixelColor(i, j, Qt::white);
        }
    }

    double Width = ui->graphicsView->geometry().width();
    double Height = ui->graphicsView->geometry().height();
   // yR =
    for (double i = xL, di = 1.0 / scale; (i - xL) * scale < Width;  i += di) {
        for (double j = yL, dj = 1.0 / scale; (j-yL) * scale < Height;  j += dj) {

            double x = i - Width / 2;
            double y = Height / 2 - j;

            x = x / 200;
            y = y / 200;

            Complex z(0, 0);
            Complex c(x, y);

            int it = -1;
            int inf = 10;
            int iterations = 100;

            for (int n = 0; n < iterations; ++n) {
                z = (z ^ 2) + c;
                if (z.abs() > inf) {
                    it = n;
                    break;
                }
            }

            if (it == -1) {
               ui->graphicsView->image->setPixelColor((i - xL) * scale, (j-yL) * scale, black);
            } else {
                ui->graphicsView->image->setPixelColor((i - xL) * scale, (j-yL) * scale,
                                     QColor(std::max(0, 255-6*it), std::max(0, 255- 4*it), std::max(0, 255-2*it)));
            }
        }
    }

    QPixmap pixmap = QPixmap::fromImage( *ui->graphicsView->image);
    ui->graphicsView->scene->addPixmap(pixmap);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->scene =new QGraphicsScene;
    ui->graphicsView->setScene(ui->graphicsView->scene);


    double width = ui->graphicsView->geometry().width();
    double height = ui->graphicsView->geometry().height();

    connect(ui->graphicsView, SIGNAL(signal(QRectF)), this, SLOT(DrawArea(QRectF)));
    connect(ui->graphicsView, SIGNAL(signal_redraw(double, double, double, double)), this, SLOT(DrawMandelbrot(double, double, double, double)));

    ui->graphicsView->image = new QImage(width, height, QImage::Format_RGB32);
    DrawMandelbrot(0, 0, width, height);
}

MainWindow::~MainWindow()
{
    delete ui;
}
