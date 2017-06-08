//
// Created by Abdullah Selek on 07/06/2017.
//

#ifndef VISIONARY_MOTION_DETECTOR_H
#define VISIONARY_MOTION_DETECTOR_H

#include "opencv2/opencv.hpp"
#include <string>

class MotionDetector {

public:
    inline MotionDetector(std::string videoPath);
    inline MotionDetector(int ceil);
    inline ~MotionDetector();

    inline std::string getVideoPath();
    inline void openCamera();
    inline CvCapture * getCapture();

private:
    std::string videoPath;
    int ceil;
    CvCapture *capture;

};

inline MotionDetector::MotionDetector(std::string videoPath) {
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
    this->capture = cvCreateCameraCapture(CV_CAP_ANY);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 1280);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 720);
    cv::namedWindow("Target", 1);
}

inline CvCapture * MotionDetector::getCapture() {
    return this->capture;
}

#endif //VISIONARY_MOTION_DETECTOR_H
