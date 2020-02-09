#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QDebug>

class ProcessThread :  public QThread
{
    Q_OBJECT
public:
    ProcessThread(QObject *parent);
    ~ProcessThread();

    void    startWork();
    void    stopWork();

protected:
    bool    bStop;
    QMutex  mutex;

    virtual void    run(){}

signals:
    void    threadFinish();
};

#endif // PROCESSTHREAD_H
