#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clsprocess.h"
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void workInterrupt();

public slots:
    void fnUpdateGUINow(int value);

private slots:
    void on_cmdStopProcess_clicked();
    void on_cmdStart_clicked();

private:
    Ui::MainWindow *ui;
    void fnInitThread();
    clsProcess *prs;
    QThread *thrd;
};

#endif // MAINWINDOW_H
