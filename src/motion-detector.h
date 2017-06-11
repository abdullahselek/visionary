//
// Created by Abdullah Selek on 07/06/2017.
//

#ifndef VISIONARY_MOTION_DETECTOR_H
#define VISIONARY_MOTION_DETECTOR_H

#include "opencv2/opencv.hpp"
#include "motion-detector-internal.h"
#include <string>

class MotionDetector {

public:
    inline MotionDetector();
    inline MotionDetector(const char * videoPath, int ceil);
    inline MotionDetector(int ceil);
    virtual inline ~MotionDetector();

    inline std::string getVideoPath();
    inline void openCamera();
    inline CvCapture * getCapture();
    inline void run();

private:
    const char *videoPath;
    int ceil;
    CvCapture *capture = nullptr;

};

static const std::string TARGET = "Target";

inline MotionDetector::MotionDetector() {

}

inline MotionDetector::MotionDetector(const char * videoPath, int ceil) {
    this->videoPath = videoPath;
    this->ceil = ceil;
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
    this->capture = createCapture(this->videoPath);
    cv::namedWindow(TARGET, 1);
}

inline CvCapture * MotionDetector::getCapture() {
    return this->capture;
}

inline CvCapture * createCapture(const char * videoPath) {
    if (videoPath != nullptr) {
        return cvCreateFileCapture(videoPath);
    } else {
        return cvCreateCameraCapture(CV_CAP_ANY);
    }
}

inline void MotionDetector::run() {
    IplImage *frame = cvQueryFrame(this->capture);
    int width = frame->width;
    int height = frame->height;
    // Surface area of the image
    int surface = width * height;
    // Hold the current surface that have changed
    int currentSurface = 0;

    IplImage *greyImage = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
    IplImage *movingAverage = cvCreateImage(cvGetSize(frame), IPL_DEPTH_32F, 3);
    IplImage *difference = nullptr;

    while (true) {
        IplImage *colorImage = cvQueryFrame(this->capture);
        // Remove false positives
        cvSmooth(colorImage, colorImage, CV_GAUSSIAN, 3, 0);
        IplImage *temp = nullptr;
        // For the first time put values in difference, temp and movingAverage
        if (difference == nullptr) {
            difference = cvCloneImage(colorImage);
            temp = cvCloneImage(colorImage);
            cvConvertScale(colorImage, movingAverage, 1.0, 0.0);
        } else {
            // Compute the average
            cvRunningAvg(colorImage, movingAverage, 0.020, NULL);
        }
        // Convert the scale of the moving average.
        cvConvertScale(movingAverage, temp, 1.0, 0.0);
        // Minus the current frame from the moving average.
        cvAbsDiff(colorImage, temp, difference);
        // Convert the image so that it can be thresholded
        cvCvtColor(difference, greyImage, CV_RGB2GRAY);
        cvThreshold(greyImage, greyImage, 70, 255, CV_THRESH_BINARY);
        // to get object blobs
        cvDilate(greyImage, greyImage, NULL, 18);
        cvErode(greyImage, greyImage, NULL, 10);
        // Find contours
        CvMemStorage *storage = cvCreateMemStorage(0);
        CvSeq *contours = 0;
        int counterCount = cvFindContours(greyImage, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        // Save contours
        CvSeq *backcontours = contours;
        // For all contours compute the area
        while (contours) {
            currentSurface += cvContourArea(contours);
            contours = contours->h_next;
        }
        // Calculate the average of contour area on the total size
        int average = currentSurface * 100;
        if (average > this->ceil) {
            std::cout << "Something is moving..." << std::endl;
        }
        // Put back the current surface to 0
        currentSurface = 0;
        // Draw the contours on the image
        // Red for external contours
        CvScalar red = cvScalar(0.0, 0.0, 255.0);
        // Green internal contours
        CvScalar green = cvScalar(0.0, 255.0, 0.0);
        // 1 contours drawn, 2 internal contours as well, 3 ...
        int levels = 1;
        cvDrawContours(colorImage, backcontours, red, green, levels, 2, CV_FILLED);
        cvShowImage(TARGET.c_str(), colorImage);
        int c = cvWaitKey(7) % 0x100;
        if (c == 27 || c == 10) {
            break;
        }
    }
}

#endif //VISIONARY_MOTION_DETECTOR_H
