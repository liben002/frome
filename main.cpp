//https://opencvguide.readthedocs.io/en/latest/opencvcpp/basics.html

#include <iostream>
#include <filesystem>
#include <regex>

#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>


int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: `./frome [path/to/video]" << std::endl;
        exit(1);
    } else if (!std::filesystem::exists(argv[1])) {
        std::cout << "Path does not exist" << std::endl;
        exit(2);
    } else if (!std::regex_match(argv[1], std::regex(R"(^([a-zA-Z0-9\s_\\.\-\(\):])+\.(mp4|mov|avi)$)"))) {
        std::cout << "Should be a video file" << std::endl;
        exit(3);
    }

    cv::VideoCapture vid (argv[1]);
    if (!vid.isOpened()) {
        std::cout << "Error opening video file" << std::endl;
        exit(4);
    }

    cv::Mat frame;
    std::vector<cv::Vec3b> colors;
    while (true) {
        vid >> frame;
        if (frame.empty()) { break; }
        unsigned long long red = 0, blue = 0, green = 0;
        for (int i = 0; i < frame.rows; i++) {
            for (int j = 0; j < frame.cols; j++) {
                blue += frame.at<cv::Vec3b>(frame.rows - 1, frame.cols - 1)[0];
                green += frame.at<cv::Vec3b>(frame.rows - 1, frame.cols - 1)[1];
                red += frame.at<cv::Vec3b>(frame.rows - 1, frame.cols - 1)[2];
            }
        }

        int frame_size = frame.rows * frame.cols;
        blue /= frame_size;
        green /= frame_size;
        red /= frame_size;
        colors.push_back(cv::Vec3b {(unsigned char) blue, (unsigned char) green, (unsigned char) red});

    }

    cv::Mat frome ((int) colors.size() * 9/16, (int) colors.size(), CV_8UC3);

    frome.at<cv::Vec3b>(0, 0) = colors[0];
    colors[0];

    for (int i = 0; i < colors.size(); i++) {
        for (int j = 0; j < frome.rows; j++) {
            frome.at<cv::Vec3b>(j, i) = colors[i];
        }
    }

    cv::imwrite("frome.png", frome, std::vector<int> {});

}
