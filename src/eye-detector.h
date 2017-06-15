//
// Created by Abdullah Selek on 15/06/2017.
//

#ifndef VISIONARY_EYE_DETECTOR_H
#define VISIONARY_EYE_DETECTOR_H

#include "opencv2/opencv.hpp"

class EyeDetector {

public:
    EyeDetector();
    EyeDetector(std::string cascadePath, const char *videoPath);
    EyeDetector(const char *imagePath);
    ~EyeDetector();

    void setCascadePath(std::string cascadePath);
    bool prepare();

private:
    std::string cascadePath;
    const char *videoPath;
    const char *imagePath;
    CvCapture *capture = nullptr;
    cv::CascadeClassifier eyeCascade;
    static const std::string TARGET;

};

const std::string EyeDetector::TARGET = "Target";

inline EyeDetector::EyeDetector() {

}

inline EyeDetector::EyeDetector(std::string cascadePath, const char *videoPath) {
    this->cascadePath = cascadePath;
    this->videoPath = videoPath;
}

inline EyeDetector::EyeDetector(const char *imagePath) {
    this->imagePath = imagePath;
}

inline EyeDetector::~EyeDetector() {

}

void EyeDetector::setCascadePath(std::string cascadePath) {
    this->cascadePath = cascadePath;
}

bool EyeDetector::prepare() {
    assert(!cascadePath.empty());
    this->eyeCascade = cv::CascadeClassifier(this->cascadePath);
    if (this->eyeCascade.empty()) {
        std::cout << "Could not load cascade classifier!" << std::endl;
        return false;
    }
    return true;
}

#endif //VISIONARY_EYE_DETECTOR_H
