#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QtMultimediaWidgets>
#include "videowidgetsurface.h"

#include <QPixmap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_cmdOpenVideoFile_clicked();
    void on_cmdCapture_clicked();
    void onMediaPlayerStop(QPixmap pix);
    void onMediaStateChanged(QMediaPlayer::MediaStatus status);

    void on_cmdSave_clicked();

Q_SIGNALS:
    void fnClearPixmap();

private:
    Ui::MainWindow *ui;
    QMediaPlayer mplayer;
    myQAbstractVideoSurface *vsurface;
    QVideoWidget vw;
    bool blnCanStop=false;
};

#endif // MAINWINDOW_H
