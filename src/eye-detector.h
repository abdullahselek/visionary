//
// Created by Abdullah Selek on 15/06/2017.
//

#ifndef VISIONARY_EYE_DETECTOR_H
#define VISIONARY_EYE_DETECTOR_H

#include "opencv2/opencv.hpp"
#include "utility.h"
#include "constants.h"

class EyeDetector {

public:
    EyeDetector();
    EyeDetector(std::string eyeCascadePath, std::string faceCascadePath, const char *videoPath);
    EyeDetector(const char *imagePath);
    ~EyeDetector();

    inline void setEyeCascadePath(std::string eyeCascadePath);
    inline void setFaceCascadePath(std::string faceCascadePath);
    inline bool prepare();
    inline void detectInImage();
    inline void detectInVideo();

private:
    std::string eyeCascadePath;
    std::string faceCascadePath;
    const char *videoPath;
    const char *imagePath;
    CvCapture *capture = nullptr;
    cv::CascadeClassifier eyeCascade;
    cv::CascadeClassifier faceCascade;

    inline void openCamera();

};

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
    cvReleaseCapture(&capture);
    cvDestroyAllWindows();
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
    cv::namedWindow(window::kTarget, 1);
    return true;
}

inline void EyeDetector::detectInImage() {
    if (this->imagePath) {
        IplImage *image = cvLoadImage(this->imagePath);
        IplImage *greyImage = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
        cvCvtColor(image, greyImage, CV_RGB2GRAY);

        CvScalar blue = cvScalar(255.0, 0.0, 0.0);
        CvScalar green = cvScalar(0.0, 255.0, 0.0);

        std::vector<cv::Rect> faces;
        cv::Mat inputArray = cv::cvarrToMat(greyImage);
        faceCascade.detectMultiScale(inputArray, faces, 1.1, 5, CV_HAAR_SCALE_IMAGE, cv::Size(50, 50));
        for (std::vector<cv::Rect>::iterator it = faces.begin() ; it != faces.end(); ++it) {
            // draw rectangle for the face
            visionary::drawRectangle(it, image, blue);

            // find eye regions and draw them
            std::vector<cv::Rect> eyes;
            eyeCascade.detectMultiScale(inputArray, eyes);
            for (std::vector<cv::Rect>::iterator it = eyes.begin() ; it != eyes.end(); ++it) {
                // draw rectangle for eyes
                visionary::drawRectangle(it, image, green);
            }
        }

        cvShowImage(window::kTarget.c_str(), image);
        cvWaitKey(0);
    }
}

inline void EyeDetector::openCamera() {
    this->capture = utility::createCapture(this->videoPath);
    cv::namedWindow(window::kTarget, 1);
}

inline void EyeDetector::detectInVideo() {
    if (this->faceCascade.empty()) {
        std::cout << "Face cascade did not instantiated!" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (this->eyeCascade.empty()) {
        std::cout << "Eye cascade did not instantiated!" << std::endl;
        exit(EXIT_FAILURE);
    }
    // open camera
    openCamera();

    // colors for drawing
    CvScalar blue = cvScalar(255.0, 0.0, 0.0);
    CvScalar green = cvScalar(0.0, 255.0, 0.0);

    while (true) {
        IplImage *frame = cvQueryFrame(this->capture);
        if (!frame) {
            std::cout << "Could not capture frame!" << std::endl;
            exit(EXIT_FAILURE);
        }
        IplImage *greyImage = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
        cvCvtColor(frame, greyImage, CV_RGB2GRAY);
        std::vector<cv::Rect> faces;
        cv::Mat inputArray = cv::cvarrToMat(greyImage);
        faceCascade.detectMultiScale(inputArray, faces, 1.1, 5, CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
        std::cout << "Faces found : " << faces.size() << std::endl;
        for (std::vector<cv::Rect>::iterator it = faces.begin() ; it != faces.end(); ++it) {
            // draw rectangle for the face
            visionary::drawRectangle(it, frame, blue);

            // find eye regions and draw them
            std::vector<cv::Rect> eyes;
            eyeCascade.detectMultiScale(inputArray, eyes);
            for (std::vector<cv::Rect>::iterator it = eyes.begin() ; it != eyes.end(); ++it) {
                // draw rectangle for eyes
                visionary::drawRectangle(it, frame, green);
            }
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

#endif //VISIONARY_EYE_DETECTOR_H
