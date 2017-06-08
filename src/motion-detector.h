//
// Created by Abdullah Selek on 07/06/2017.
//

#ifndef VISIONARY_MOTION_DETECTOR_H
#define VISIONARY_MOTION_DETECTOR_H

#include "opencv2/opencv.hpp"
#include <string>

class MotionDetector {

public:
    MotionDetector(std::string videoPath);
    ~MotionDetector();

    std::string getVideoPath();

private:
    std::string videoPath;

};

MotionDetector::MotionDetector(std::string videoPath) {
    this->videoPath = videoPath;
}

MotionDetector::~MotionDetector() {

}

std::string MotionDetector::getVideoPath() {
    return videoPath;
}

#endif //VISIONARY_MOTION_DETECTOR_H
