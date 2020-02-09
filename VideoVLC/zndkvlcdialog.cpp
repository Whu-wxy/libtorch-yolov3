#include "zndkvlcdialog.h"
#include <QDebug>

ZNDKVLCDialog::ZNDKVLCDialog()
{
    setMinimumSize(800, 600);
    resize(800, 600);

    m_instance = new VlcInstance(VlcCommon::args());
    m_player = new VlcMediaPlayer(m_instance);
    m_vlcWidget = new ZNDKVLCWidget(m_player);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_vlcWidget);

    m_stream = new ZNDKVideoStream(Vlc::YUVFormat);
    connect(m_stream, SIGNAL(sendImage(QImage)),m_vlcWidget,SLOT(getImage(QImage)), Qt::AutoConnection);
    m_stream->setCallbacks(m_player);

    bool localFile = true;
    QString url("/home/wxy/QtWork/test.mp4");
    m_media = new VlcMedia(url, localFile, m_instance);
   // m_media->setOption(":network-caching=30");

    m_player->open(m_media);
   // m_player->setPlaybackRate(0.6); //bug?

    m_stream->init(m_player);

}

ZNDKVLCDialog::~ZNDKVLCDialog()
{
    delete m_player;
    delete m_media;
    delete m_instance;
}
