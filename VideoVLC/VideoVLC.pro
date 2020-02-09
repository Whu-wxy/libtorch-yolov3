QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Darknet.cpp \
    darknetmanager.cpp \
    imgprocessthread.cpp \
    imgutils.cpp \
    main.cpp \
    processthread.cpp \
    zndkvideostream.cpp \
    zndkvlcdialog.cpp \
    zndkvlcwidget.cpp

HEADERS += \
    Darknet.h \
    darknetmanager.h \
    imgprocessthread.h \
    imgutils.h \
    processthread.h \
    zndkvideostream.h \
    zndkvlcdialog.h \
    zndkvlcwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



win32 {
INCLUDEPATH += D:\OpenCVMinGW3.4.1\include
LIBS += D:\OpenCVMinGW3.4.1\bin\libopencv_*.dll

LIBS       += -LD:/VLC-Qt_1.1.0_win32_mingw/bin -lVLCQtCore -lVLCQtWidgets
INCLUDEPATH += D:/VLC-Qt_1.1.0_win32_mingw/include
}

unix{
#opencv
INCLUDEPATH += /home/wxy/opencv-3.4.1/build/include
DEPENDPATH += /home/wxy/opencv-3.4.1/build/

LIBS += -L/home/wxy/opencv-3.4.1/build/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

#vlc-qt
LIBS       += -L/usr/local/lib -lVLCQtCore -lVLCQtWidgets
INCLUDEPATH += /usr/local/include

#libtorch
INCLUDEPATH += /home/wxy/libtorch/include/torch/csrc/api/include \
/home/wxy/libtorch/include
DEPENDPATH += /home/wxy/libtorch/include/torch/csrc/api/include \
/home/wxy/libtorch/include

LIBS += -L/home/wxy/libtorch/lib -lc10 \
-lcaffe2_detectron_ops \
-lcaffe2_module_test_dynamic \
-lclog -lcpuinfo \
-lonnx -lonnx_proto \
-ltorch
}
