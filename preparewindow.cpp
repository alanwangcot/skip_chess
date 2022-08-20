#include "preparewindow.h"
#include "ui_preparewindow.h"

PrepareWindow::PrepareWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrepareWindow)
{
    ui->setupUi(this);
}

PrepareWindow::~PrepareWindow()
{
    delete ui;
}

void PrepareWindow::on_createButton_clicked()
{

}

