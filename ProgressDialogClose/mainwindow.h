#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clsprocess.h"
#include <QThread>
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void fnUpdateGUINow(int value);

    void fnStop();
private slots:
    void on_cmdStart_clicked();

private:
    Ui::MainWindow *ui;
    void fnInitThread();
    clsProcess *prs;
    QThread *thrd;
    Dialog *dlg;
};

#endif // MAINWINDOW_H
