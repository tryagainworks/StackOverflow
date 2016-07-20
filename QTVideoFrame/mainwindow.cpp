#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),mplayer(parent, QMediaPlayer::VideoSurface)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if(mplayer.state()==QMediaPlayer::PausedState){
        vsurface->stop();
        vsurface->deleteLater();
        mplayer.stop();
    }

	delete ui;
}

void MainWindow::on_cmdOpenVideoFile_clicked()
{
	QFileDialog fd;
	fd.show();
	fd.exec();
	QString strFileName = fd.selectedFiles().at(0);
	vsurface = new myQAbstractVideoSurface();
    mplayer.setVideoOutput(vsurface);

	connect(vsurface, SIGNAL(fnSurfaceStopped(QPixmap)),
	        this, SLOT(onMediaPlayerStop(QPixmap)),Qt::QueuedConnection);

    connect(&mplayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(onMediaStateChanged(QMediaPlayer::MediaStatus)));

    connect(this, SIGNAL(fnClearPixmap()),
            vsurface, SLOT(fnClearPixmap()),Qt::QueuedConnection);

	mplayer.setMedia(QUrl::fromLocalFile(strFileName));
}

void MainWindow::on_cmdCapture_clicked()
{
    emit fnClearPixmap();
    mplayer.setPosition(ui->sldDuration->value()*1000);
    mplayer.setMuted(true);
    mplayer.play();
}

void MainWindow::onMediaPlayerStop(QPixmap pix)
{
	ui->lblActual->setPixmap(pix);
	ui->lblActual->update();
    mplayer.pause();
}

void MainWindow::onMediaStateChanged(QMediaPlayer::MediaStatus status)
{
    if(status==QMediaPlayer::LoadedMedia)
    {
        qDebug()<<"duration="<<mplayer.duration()/1000.0f;
        ui->sldDuration->setMaximum(static_cast<int>(mplayer.duration()/1000));
        ui->sldDuration->setMinimum(0);
    }else{
        qDebug()<<"media loading";
    }
}

void MainWindow::on_cmdSave_clicked()
{
    QMessageBox::information(this,"Save path","Enter save path in next line of code");
    //ui->lblActual->pixmap()->save("save path here","PNG");
}
