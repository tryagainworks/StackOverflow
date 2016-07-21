#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

void MainWindow::fnInitThread()
{
	prs = new clsProcess();
	thrd = new QThread();
	prs->moveToThread(thrd);
	connect( thrd, SIGNAL(started()), prs, SLOT(doWork()) );
	connect( prs, SIGNAL(workFinished()), thrd, SLOT(quit()) );
	connect( this, SIGNAL(workInterrupt()), prs, SLOT(doWorkInterrupt()),Qt::QueuedConnection);
	//gui update
	connect( prs, SIGNAL(fnUpdateGUI(int)), this, SLOT(fnUpdateGUINow(int)) );
	//automatically delete thrd and prs object when work is done:
	connect( thrd, SIGNAL(finished()), prs, SLOT(deleteLater()) );
	connect( thrd, SIGNAL(finished()), thrd, SLOT(deleteLater()) );

	thrd->start();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::fnUpdateGUINow(int value)
{
	ui->progressBar->setValue(value);
}

void MainWindow::on_cmdStopProcess_clicked()
{
	emit workInterrupt();
}

void MainWindow::on_cmdStart_clicked()
{
	fnInitThread();
}
