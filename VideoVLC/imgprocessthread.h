#ifndef IMGPROCESSTHREAD_H
#define IMGPROCESSTHREAD_H

#include <QObject>
#include <QQueue>

#include "processthread.h"
#include "darknetmanager.h"

#include "opencv2/opencv.hpp"//添加Opencv相关头文件
#include "opencv2/highgui/highgui.hpp"

class ImgProcessThread : public ProcessThread
{
    Q_OBJECT

public:
    ImgProcessThread(QObject *parent);
    ~ImgProcessThread();

    void    addImage(cv::Mat img);

signals:
    void    finishOne(cv::Mat);

protected:
    virtual void    run();
    void    loadModel();
    void    predict();

    QQueue<cv::Mat>  m_imgQue;
    DarknetManager m_netManager;
};

#endif // IMGPROCESSTHREAD_H
