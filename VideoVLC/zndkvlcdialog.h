#ifndef ZNDKVLCDIALOG_H
#define ZNDKVLCDIALOG_H

#include <QObject>
#include <QDialog>
#include <QHBoxLayout>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/YUVVideoFrame.h>

#include "zndkvlcwidget.h"

class ZNDKVLCDialog : public QDialog
{
    Q_OBJECT
public:
    ZNDKVLCDialog();
    virtual ~ZNDKVLCDialog();

private:
    QTimer*  m_timer;

    ZNDKVLCWidget* m_vlcWidget;
    VlcInstance *m_instance;
    VlcMedia *m_media;
    VlcMediaPlayer *m_player;
    ZNDKVideoStream* m_stream;
};

#endif // ZNDKVLCDIALOG_H
