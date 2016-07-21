#include "clsprocess.h"
#include <qdebug.h>

clsProcess::clsProcess(QObject *parent) : QObject(parent)
{

}

void clsProcess::doWork()
{
	iCount++;
    emit fnUpdateGUI(iCount);
	qDebug()<<"Process done here" << iCount << "\n";
    //pause the current thread for 100 millisecods (1/10 seconds)
	this->thread()->msleep(100);
    if(iCount>=50)
	{
		emit workFinished();
    }else{
        // allow the thread's event loop to process other events before doing more "work"
        // for instance, your start/stop signals from the MainWindow
        QMetaObject::invokeMethod( this, "doWork", Qt::QueuedConnection);
    }
}

