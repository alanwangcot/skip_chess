#ifndef PREPAREWINDOW_H
#define PREPAREWINDOW_H

#include <QDialog>
#include <QString>

namespace Ui {
class PrepareWindow;
}

class PrepareWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PrepareWindow(QWidget *parent = nullptr);
    ~PrepareWindow();
signals:
    void serverStarted(QString ip);

public slots:


private:
    Ui::PrepareWindow *ui;
};

#endif // PREPAREWINDOW_H
