#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "vtk-8.1/vtkAutoInit.h"
// VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#include <QMainWindow>
#include <QDir>
#include <QDebug>
#include <QFileDialog>

#include "vtk-8.1/vtkPolyDataMapper.h"
#include "vtk-8.1/vtkRenderer.h"
#include "vtk-8.1/vtkRenderWindow.h"
#include "vtk-8.1/vtkSphereSource.h"
#include "vtk-8.1/vtkSmartPointer.h"
#include "vtk-8.1/vtkProperty.h"
#include "vtk-8.1/vtkRenderWindowInteractor.h"
#include "vtk-8.1/QVTKOpenGLWidget.h"
#include "vtk-8.1/vtkInteractorStyleTrackballCamera.h"
#include "vtk-8.1/QVTKWidget.h"
#include "vtk-8.1/vtkSimplePointsReader.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QString openFile();

    QVTKWidget *vtkWidget;
    vtkSmartPointer<vtkSimplePointsReader> reader;
    vtkSmartPointer<vtkPolyDataMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkRenderer *renderer;
    vtkRenderWindow *renderWindow;
    vtkRenderWindowInteractor *interactor;
    vtkInteractorStyleTrackballCamera *style;

    void init();
};

#endif // MAINWINDOW_H
