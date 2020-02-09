#include "zndkvlcwidget.h"
#include "zndkvlcdialog.h"
#include <QApplication>
#include <VLCQtCore/Common.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VlcCommon::setPluginPath(a.applicationDirPath() + "/plugins");

    ZNDKVLCDialog w;
    w.show();

    return a.exec();
}
