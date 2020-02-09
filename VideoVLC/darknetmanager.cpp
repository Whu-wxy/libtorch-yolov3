#include "darknetmanager.h"

DarknetManager::DarknetManager(torch::Device device)
    :m_darknet("/home/wxy/QtWork/libtorch-yolov3/models/yolov3.cfg", &device)
{
    // input image size for YOLO v3
    int input_image_size = 416;

    //Darknet net("/home/wxy/QtWork/libtorch-yolov3/models/yolov3.cfg", &device);

    map<string, string> *info = m_darknet.get_net_info();

    info->operator[]("height") = std::to_string(input_image_size);

    std::cout << "loading weight ..." << endl;
    m_darknet.load_weights("/home/wxy/QtWork/libtorch-yolov3/models/yolov3.weights");
    std::cout << "weight loaded ..." << endl;

    m_darknet.to(device);

    torch::NoGradGuard no_grad;
    m_darknet.eval();
}

DarknetManager::~DarknetManager()
{

}

cv::Mat DarknetManager::predict(cv::Mat origin_image)
{
    cv::Mat resized_image = origin_image.clone();
    // input image size for YOLO v3
    int input_image_size = 416;

    cv::cvtColor(origin_image, resized_image,  cv::COLOR_BGR2RGB);
    cv::resize(resized_image, resized_image, cv::Size(input_image_size, input_image_size));

    cv::Mat img_float;
    resized_image.convertTo(img_float, CV_32F, 1.0/255);

    torch::DeviceType device_type;

    if (torch::cuda::is_available() ) {
        device_type = torch::kCUDA;
    } else {
        device_type = torch::kCPU;
    }
    torch::Device device(device_type);

    auto img_tensor = torch::from_blob(img_float.data, {1, input_image_size, input_image_size, 3}).to(device);
    img_tensor = img_tensor.permute({0,3,1,2});

    auto start = std::chrono::high_resolution_clock::now();

    auto output = m_darknet.forward(img_tensor);
    // filter result by NMS
    // class_num = 80
    // confidence = 0.6
    auto result = m_darknet.write_results(output, 80, 0.6, 0.4);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    // It should be known that it takes longer time at first time
    std::cout << "inference taken : " << duration.count() << " ms" << endl;

    if (result.dim() == 1)
    {
        std::cout << "no object found" << endl;
    }
    else
    {
        int obj_num = result.size(0);

      //  std::cout << obj_num << " objects found" << endl;

        float w_scale = float(origin_image.cols) / input_image_size;
        float h_scale = float(origin_image.rows) / input_image_size;

        result.select(1,1).mul_(w_scale);
        result.select(1,2).mul_(h_scale);
        result.select(1,3).mul_(w_scale);
        result.select(1,4).mul_(h_scale);

        auto result_data = result.accessor<float, 2>();

        for (int i = 0; i < result.size(0) ; i++)
        {
            cv::rectangle(origin_image, cv::Point(result_data[i][1], result_data[i][2]), cv::Point(result_data[i][3], result_data[i][4]), cv::Scalar(0, 0, 255), 1, 1, 0);
        }
    }
    return origin_image;
}
