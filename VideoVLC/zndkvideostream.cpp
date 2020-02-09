#include "zndkvideostream.h"
#include <QDebug>
#include <QThread>

ZNDKVideoStream::ZNDKVideoStream(Vlc::RenderFormat format, QObject *parent)
    : VlcVideoStream(format, parent)
{
    frameNumber = 0;
}

ZNDKVideoStream::~ZNDKVideoStream()
{

}

void ZNDKVideoStream::frameUpdated()
{
    std::shared_ptr<const VlcYUVVideoFrame> pFrame = std::dynamic_pointer_cast<const VlcYUVVideoFrame>(renderFrame());
    if (!pFrame) {
        return; //LCOV_EXCL_LINE
    }

    int rows = pFrame->height + pFrame->height / 2;
    int cols = pFrame->width;
    int matType = CV_8UC1;

    cv::Mat myuv(rows,cols,matType,(void*)pFrame->frameBuffer.data());
    cv::Mat mrgb(pFrame->height, pFrame->width, CV_8UC3);
    cv::cvtColor(myuv, mrgb, CV_YUV2RGB_I420);
    QImage img((const unsigned char *)(mrgb.data), mrgb.cols, mrgb.rows, mrgb.cols * 3, QImage::Format_RGB888);
    img.rgbSwapped();

    toSendImage(img);

    //qDebug()<<frameNumber++;
}

void ZNDKVideoStream::toSendImage(QImage img)
{
    emit sendImage(img);
}
