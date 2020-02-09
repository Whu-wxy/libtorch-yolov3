#include "processthread.h"

ProcessThread::ProcessThread(QObject *parent)
    :QThread(parent)
{
    bStop = false;
}

ProcessThread::~ProcessThread()
{

}

void ProcessThread::startWork()
{
    bStop = false;
    start();
}

void ProcessThread::stopWork()
{
    if(isRunning())
    {
        bStop = true;
        quit();
        wait();
    }
}
