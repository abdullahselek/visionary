//
// Created by Abdullah Selek on 15/06/2017.
//

#ifndef VISIONARY_EYE_DETECTOR_H
#define VISIONARY_EYE_DETECTOR_H

#include "opencv2/opencv.hpp"

class EyeDetector {

public:
    EyeDetector();
    EyeDetector(std::string eyeCascadePath, std::string faceCascadePath, const char *videoPath);
    EyeDetector(const char *imagePath);
    ~EyeDetector();

    inline void setEyeCascadePath(std::string eyeCascadePath);
    inline void setFaceCascadePath(std::string faceCascadePath);
    inline bool prepare();

private:
    std::string eyeCascadePath;
    std::string faceCascadePath;
    const char *videoPath;
    const char *imagePath;
    CvCapture *capture = nullptr;
    cv::CascadeClassifier eyeCascade;
    cv::CascadeClassifier faceCascade;
    static const std::string TARGET;

};

const std::string EyeDetector::TARGET = "Target";

inline EyeDetector::EyeDetector() {

}

inline EyeDetector::EyeDetector(std::string eyeCascadePath,
                                std::string faceCascadePath,
                                const char *videoPath) {
    this->eyeCascadePath = eyeCascadePath;
    this->faceCascadePath = faceCascadePath;
    this->videoPath = videoPath;
}

inline EyeDetector::EyeDetector(const char *imagePath) {
    this->imagePath = imagePath;
}

inline EyeDetector::~EyeDetector() {

}

inline void EyeDetector::setEyeCascadePath(std::string eyeCascadePath) {
    this->eyeCascadePath = eyeCascadePath;
}

inline void EyeDetector::setFaceCascadePath(std::string faceCascadePath) {
    this->faceCascadePath = faceCascadePath;
}

inline bool EyeDetector::prepare() {
    assert(!eyeCascadePath.empty());
    this->eyeCascade = cv::CascadeClassifier(this->eyeCascadePath);
    if (this->eyeCascade.empty()) {
        std::cout << "Could not load eye cascade classifier!" << std::endl;
        return false;
    }
    assert(!faceCascadePath.empty());
    this->faceCascade = cv::CascadeClassifier(this->faceCascadePath);
    if (this->faceCascade.empty()) {
        std::cout << "Could not load face cascade classifier!" << std::endl;
        return false;
    }
    return true;
}



#endif //VISIONARY_EYE_DETECTOR_H
