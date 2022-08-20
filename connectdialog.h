#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = nullptr);
    ~ConnectDialog();
signals:
    void confirmButtonClicked(QString ip);
private slots:

    void on_confirmButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ConnectDialog *ui;
    QString input;
};

#endif // CONNECTDIALOG_H
