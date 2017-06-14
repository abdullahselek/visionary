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
    cvReleaseCapture(&capture);
    cvDestroyAllWindows();
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
    if (this->faceCascade.empty()) {
        return;
    }

    openCamera();
    CvScalar green = cvScalar(0.0, 255.0, 0.0);

    while (true) {
        IplImage *frame = cvQueryFrame(this->capture);
        IplImage *grayImage = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
        cvCvtColor(frame, grayImage, CV_RGB2GRAY);
        std::vector<cv::Rect> faces;
        cv::Mat inputArray = cv::cvarrToMat(grayImage);
        faceCascade.detectMultiScale(inputArray, faces, 1.1, 5, CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
        for (std::vector<cv::Rect>::iterator it = faces.begin() ; it != faces.end(); ++it) {
            cv::Rect rect = *it;
            CvPoint point1;
            point1.x = rect.x;
            point1.y = rect.y;
            CvPoint point2;
            point2.x = rect.x + rect.width;
            point2.y = rect.y + rect.height;
            cvRectangle(frame, point1, point2, green, 2);
            cvShowImage(TARGET.c_str(), frame);

            int c = cvWaitKey(1);
            if (c == 27 || c == 10) {
                break;
            }
        }
    }
}

#endif //VISIONARY_FACE_DETECTOR_H
