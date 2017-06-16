//
// Created by Selek, Abdullah on 14.06.17.
//

#ifndef VISIONARY_FACE_DETECTOR_H
#define VISIONARY_FACE_DETECTOR_H

#include "opencv2/opencv.hpp"
#include "utility.h"
#include "constants.h"

class FaceDetector {

public:
    FaceDetector();
    FaceDetector(std::string cascadePath,
                 source::type sourceType,
                 const char *sourcePath);
    ~FaceDetector();
    inline void openCamera();
    inline void detectInImage();
    inline void detectInVideo();

private:
    std::string cascadePath;
    const char *sourcePath;
    CvCapture *capture = nullptr;
    cv::CascadeClassifier cascadeClassifier;

};

inline FaceDetector::FaceDetector() {

}

inline FaceDetector::FaceDetector(std::string cascadePath,
                                  source::type sourceType,
                                  const char *sourcePath) {
    this->cascadePath = cascadePath;
    if (sourceType == source::type::video) {
        this->sourcePath = sourcePath;
    } else {
        this->sourcePath = sourcePath;
    }
}

inline FaceDetector::~FaceDetector() {
    cvReleaseCapture(&capture);
    cvDestroyAllWindows();
}

inline void FaceDetector::openCamera() {
    this->capture = utility::createCapture(this->sourcePath);
    cv::namedWindow(window::kTarget, 1);
}

inline void FaceDetector::detectInImage() {
    assert(!cascadePath.empty());
    this->cascadeClassifier = cv::CascadeClassifier(this->cascadePath);
    if (this->cascadeClassifier.empty()) {
        return;
    }
    if (this->sourcePath) {
        // create green scalar
        CvScalar green = cvScalar(0.0, 255.0, 0.0);

        IplImage *image = cvLoadImage(this->sourcePath);
        IplImage *greyImage = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
        cvCvtColor(image, greyImage, CV_RGB2GRAY);

        std::vector<cv::Rect> faces;
        cv::Mat inputArray = cv::cvarrToMat(greyImage);
        cascadeClassifier.detectMultiScale(inputArray, faces, 1.1, 5, CV_HAAR_SCALE_IMAGE, cv::Size(50, 50));
        for (std::vector<cv::Rect>::iterator it = faces.begin() ; it != faces.end(); ++it) {
            visionary::drawRectangleOnFace(it, image, green);
        }

        cvShowImage(window::kTarget.c_str(), image);

        // release grey image
        cvReleaseImage(&greyImage);

        cvWaitKey(0);
    }
}

inline void FaceDetector::detectInVideo() {
    assert(!cascadePath.empty());
    this->cascadeClassifier = cv::CascadeClassifier(this->cascadePath);
    if (this->cascadeClassifier.empty()) {
        return;
    }

    while (true) {
        IplImage *frame = cvQueryFrame(this->capture);
        if (!frame) {
            std::cout << "Could not capture frame!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // create green scalar
        CvScalar green = cvScalar(0.0, 255.0, 0.0);

        IplImage *greyImage = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
        cvCvtColor(frame, greyImage, CV_RGB2GRAY);
        std::vector<cv::Rect> faces;
        cv::Mat inputArray = cv::cvarrToMat(greyImage);
        cascadeClassifier.detectMultiScale(inputArray, faces, 1.1, 5, CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
        std::cout << "Faces found : " << faces.size() << std::endl;
        for (std::vector<cv::Rect>::iterator it = faces.begin() ; it != faces.end(); ++it) {
            visionary::drawRectangleOnFace(it, frame, green);
        }
        cvShowImage(window::kTarget.c_str(), frame);

        // release grey image
        cvReleaseImage(&greyImage);

        int c = cvWaitKey(1);
        if (c == 27) {
            break;
        }
    }
}

#endif //VISIONARY_FACE_DETECTOR_H
