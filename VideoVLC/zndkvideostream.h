#ifndef ZNDKVIDEOSTREAM_H
#define ZNDKVIDEOSTREAM_H

#include <QObject>
#include <QImage>

#include <VLCQtCore/VideoStream.h>
#include <VLCQtCore/YUVVideoFrame.h>

#include "opencv2/opencv.hpp"//添加Opencv相关头文件
#include "opencv2/highgui/highgui.hpp"

class ZNDKVideoStream : public VlcVideoStream
{
    Q_OBJECT
public:
    ZNDKVideoStream(Vlc::RenderFormat format, QObject *parent = 0);
    virtual ~ZNDKVideoStream();

signals:
    void    sendImage(QImage);

private:
    int frameNumber;

    virtual void frameUpdated();

    void    toSendImage(QImage);
};

#endif // ZNDKVIDEOSTREAM_H
