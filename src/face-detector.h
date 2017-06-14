//
// Created by Selek, Abdullah on 14.06.17.
//

#ifndef VISIONARY_FACE_DETECTOR_H
#define VISIONARY_FACE_DETECTOR_H

#include "opencv2/opencv.hpp"

class FaceDetector {

public:
    FaceDetector();
    FaceDetector(std::string cascadePath, const char * videoPath);
    ~FaceDetector();
    void run();

private:
    std::string cascadePath;
    const char *videoPath;
    CvCapture *capture = nullptr;
    cv::CascadeClassifier faceCascade;
    static const std::string TARGET;

    inline void openCamera();
    inline CvCapture * createCapture(const char * videoPath);

};

const std::string FaceDetector::TARGET = "Target";

inline FaceDetector::FaceDetector() {

}

inline FaceDetector::FaceDetector(std::string cascadePath, const char * videoPath) {
    this->cascadePath = cascadePath;
    this->videoPath = videoPath;
}

inline FaceDetector::~FaceDetector() {

}

inline void FaceDetector::openCamera() {
    this->capture = createCapture(this->videoPath);
    cv::namedWindow(TARGET, 1);
}

inline CvCapture * FaceDetector::createCapture(const char * videoPath) {
    if (videoPath != nullptr) {
        return cvCreateFileCapture(videoPath);
    } else {
        return cvCreateCameraCapture(CV_CAP_ANY);
    }
}

inline void FaceDetector::run() {
    assert(!cascadePath.empty());
    this->faceCascade = cv::CascadeClassifier(this->cascadePath);

}

#endif //VISIONARY_FACE_DETECTOR_H
