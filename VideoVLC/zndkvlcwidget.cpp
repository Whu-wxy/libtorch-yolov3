#include "zndkvlcwidget.h"
#include <QDebug>
#include <QMetaType>

ZNDKVLCWidget::ZNDKVLCWidget(VlcMediaPlayer *player, QWidget *parent)
    : VlcWidgetVideo(player, parent)
{
    qRegisterMetaType<cv::Mat>("cv::Mat");

    m_pixmap = NULL;

    setAutoFillBackground(false);

    m_modelThread = new ImgProcessThread(this);
    connect(m_modelThread, SIGNAL(finishOne(cv::Mat)), this, SLOT(finishOnePred(cv::Mat)), Qt::DirectConnection);
    m_modelThread->startWork();
}

ZNDKVLCWidget::~ZNDKVLCWidget()
{
    if(m_pixmap != NULL)
    {
        delete m_pixmap;
        m_pixmap = NULL;
    }
    m_modelThread->stopWork();
    if(m_modelThread != NULL)
    {
        delete m_modelThread;
        m_modelThread = NULL;
    }
}

void ZNDKVLCWidget::paintEvent(QPaintEvent*)
{
    QRect rect = this->rect();
    if(m_pixmap != NULL)
    {
        if(m_pixmap->width() != rect.width() || m_pixmap->height() != rect.height())
        {
            delete m_pixmap;
            m_pixmap = NULL;
        }
    }
    if(m_pixmap == NULL)
    {
        m_pixmap = new QPixmap(rect.size());
        if(m_pixmap == NULL) return;
    }

    QPainter painter(m_pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.drawImage(rect, m_image);


    QPainter basePainter(this);
    basePainter.begin(this);
    basePainter.setRenderHint(QPainter::Antialiasing, true);
    basePainter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    basePainter.drawPixmap(rect, *m_pixmap);
    basePainter.end();
}

void ZNDKVLCWidget::getImage(QImage img)
{
    if(m_modelThread != NULL)
        m_modelThread->addImage(QImageToMat(img));
}

void ZNDKVLCWidget::finishOnePred(cv::Mat img)
{
    m_image = MatToQImage(img);
    repaint();
}
