#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    // needed to ensure appropriate OpenGL context is created for VTK rendering.
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
