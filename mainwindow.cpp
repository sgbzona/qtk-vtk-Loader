#include "mainwindow.h"
#include "ui_mainwindow.h"

///Based on:
///https://lorensen.github.io/VTKExamples/site/Cxx/IO/SimplePointsReader/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();

}

MainWindow::~MainWindow()
{
    delete ui;
}


QString MainWindow::openFile()
{

    //load file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open xyz File"), "/", tr("Files (*.xyz)"));

    if(fileName.isNull() || fileName.isEmpty()){
        return "0";
    }

    return fileName;
}

void MainWindow::on_pushButton_clicked()
{
    qApp->exit();
}

void MainWindow::on_pushButton_2_clicked()
{

    QString tmp = openFile();

    if(tmp == "0"){
        return;
    }

    // Convert QString
    QByteArray ba = tmp.toLocal8Bit();
    const char *theFile = ba.data();

    qDebug() << "File:" << theFile;
    reader = vtkSmartPointer<vtkSimplePointsReader>::New();
    reader->SetFileName(theFile);

    // we update all

    reader->Update();

    mapper->SetInputConnection(reader->GetOutputPort());
    mapper->Update();

    renderer->ResetCamera();

    actor->SetMapper(mapper);

    renderWindow->Render();
    interactor->Start();

}

void MainWindow::init()
{
    // Create vtk objects
    //we need to change this, QVTKWidget is deprecated
    vtkWidget = new QVTKWidget(this);

    reader = vtkSmartPointer<vtkSimplePointsReader>::New();
    reader->SetFileName("");
    reader->Update();

    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());

    // Create mapper and actor
    actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetPointSize(4);

    // Create renderer
    renderer = vtkRenderer::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0.3, 0.6, 0.3);

    // QVTKWidget has render window and interactor
    renderWindow = vtkWidget->GetRenderWindow();
    renderWindow->AddRenderer(renderer);
    interactor = renderWindow->GetInteractor();

    style = vtkInteractorStyleTrackballCamera::New();
    interactor->SetInteractorStyle(style);

    // Put widget
    ui->tkwidget->addWidget(vtkWidget);

}
