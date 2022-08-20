#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_confirmButton_clicked()
{
    input = ui->lineEdit->text();
    emit ConnectDialog::confirmButtonClicked(input);
    this->close();
}


void ConnectDialog::on_cancelButton_clicked()
{
    this->close();
}

