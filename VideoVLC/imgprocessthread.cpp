#include "imgprocessthread.h"
#include <QMetaType>

ImgProcessThread::ImgProcessThread(QObject *parent)
    : ProcessThread(parent)
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
}

ImgProcessThread::~ImgProcessThread()
{
    m_imgQue.clear();
}

void ImgProcessThread::run()
{
    while(1)
    {
        if(bStop)
            break;

        mutex.lock();
        predict();
        mutex.unlock();

        usleep(5);
    }
    emit threadFinish();
}


void ImgProcessThread::addImage(cv::Mat img)
{
    mutex.lock();
    if(m_imgQue.count() == 5)
        m_imgQue.pop_front();

    m_imgQue.append(img);
    mutex.unlock();
}

void ImgProcessThread::loadModel()
{
    m_netManager.loadModel();
}

void ImgProcessThread::predict()
{
    if(m_imgQue.count() == 0)
        return;

    cv::Mat img = m_imgQue.takeFirst();
    cv::Mat res = m_netManager.predict(img);
    emit finishOne(res);
}
