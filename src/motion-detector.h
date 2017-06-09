//
// Created by Abdullah Selek on 07/06/2017.
//

#ifndef VISIONARY_MOTION_DETECTOR_H
#define VISIONARY_MOTION_DETECTOR_H

#include "opencv2/opencv.hpp"
#include <string>

class MotionDetector {

public:
    inline MotionDetector(const char * videoPath);
    inline MotionDetector(int ceil);
    inline ~MotionDetector();

    inline std::string getVideoPath();
    inline void openCamera();
    inline CvCapture * getCapture();

private:
    const char *videoPath;
    int ceil;
    CvCapture *capture;

};

inline MotionDetector::MotionDetector(const char * videoPath) {
    this->videoPath = videoPath;
}

inline MotionDetector::MotionDetector(int ceil) {
    this->ceil = ceil;
}

inline MotionDetector::~MotionDetector() {

}

inline std::string MotionDetector::getVideoPath() {
    return videoPath;
}

inline void MotionDetector::openCamera() {
    if (this->videoPath == nullptr) {
        this->capture = cvCreateFileCapture(this->videoPath);
    } else {
        this->capture = cvCreateCameraCapture(CV_CAP_ANY);
    }
    cv::namedWindow("Target", 1);
}

inline CvCapture * MotionDetector::getCapture() {
    return this->capture;
}

#endif //VISIONARY_MOTION_DETECTOR_H
