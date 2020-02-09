#ifndef DARKNETMANAGER_H
#define DARKNETMANAGER_H

#include "opencv2/opencv.hpp"//添加Opencv相关头文件
#include "opencv2/highgui/highgui.hpp"

#include "Darknet.h"

#undef slots
#include "torch/torch.h"
#include "torch/jit.h"
#include "torch/nn.h"
#include "torch/script.h"
#define slots Q_SLOTS

#include <cmath>
#include <time.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <QString>
#include <QImage>
#include <QFile>
#include <chrono>

using namespace std;
using namespace std::chrono;

class DarknetManager
{
public:
    DarknetManager(torch::Device = torch::Device(torch::kCPU));
    ~DarknetManager();

    cv::Mat    predict(cv::Mat);

private:
    Darknet     m_darknet;

};

#endif // DARKNETMANAGER_H
