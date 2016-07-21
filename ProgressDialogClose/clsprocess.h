#ifndef CLSPROCESS_H
#define CLSPROCESS_H

#include <QObject>
#include <QThread>
#include <QTimer>

class clsProcess : public QObject
{
    Q_OBJECT
public:
    explicit clsProcess(QObject *parent = 0);

signals:
    void workFinished();
    void fnUpdateGUI(int intValue);

public slots:
    void doWork();

private slots:
private:
    int iCount=0;
};

#endif // CLSPROCESS_H
