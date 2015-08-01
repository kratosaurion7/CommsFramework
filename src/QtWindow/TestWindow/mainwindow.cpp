#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "PackageFile.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnPackagerTest_clicked()
{
    PackageFile* pak = new PackageFile();
    pak->AddFile("C:\\temp\\test_file.txt");

    int size = 0;

    auto content = pak->GetFile("C:\\temp\\test_file.txt",size);

    delete(content);

    pak->Save("C:\\temp\\out.pak");

    delete(pak);

}
