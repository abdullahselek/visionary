//
// Created by Abdullah Selek on 07/06/2017.
//

#ifndef VISIONARY_MOTION_DETECTOR_H
#define VISIONARY_MOTION_DETECTOR_H

#include "opencv2/opencv.hpp"
#include "motion-detector-internal.h"
#include "utility.h"
#include "constants.h"
#include <string>

class MotionDetector {

public:
    inline MotionDetector();
    inline MotionDetector(const char * videoPath, int ceil);
    inline MotionDetector(int ceil);
    virtual inline ~MotionDetector();

    inline void setVideoPath(const char * videoPath);
    inline void setCeil(int ceil);
    inline const char * getVideoPath();
    inline int getCeil();
    inline void openCamera();
    inline CvCapture * getCapture();
    inline void run();

private:
    const char *videoPath;
    int ceil = 0;
    CvCapture *capture = nullptr;

};

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
    cvReleaseCapture(&capture);
    cvDestroyAllWindows();
}

inline void MotionDetector::setVideoPath(const char * videoPath) {
    this->videoPath = videoPath;
}

inline void MotionDetector::setCeil(int ceil) {
    this->ceil = ceil;
}

inline const char * MotionDetector::getVideoPath() {
    return videoPath;
}

inline int MotionDetector::getCeil() {
    return ceil;
}

inline void MotionDetector::openCamera() {
    this->capture = createCapture(this->videoPath);
    cv::namedWindow(window::kTarget, 1);
}

inline CvCapture * MotionDetector::getCapture() {
    return this->capture;
}

inline CvCapture * createCapture(const char * videoPath) {
    return utility::createCapture(videoPath);
}

inline void MotionDetector::run() {
    IplImage *frame = cvQueryFrame(this->capture);
    if (!frame) {
        std::cout << "Could not capture frame!" << std::endl;
        exit(EXIT_FAILURE);
    }
    int width = frame->width;
    int height = frame->height;
    // Surface area of the image
    int surface = width * height;
    // Hold the current surface that have changed
    int currentSurface = 0;

    IplImage *greyImage = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
    IplImage *movingAverage = cvCreateImage(cvGetSize(frame), IPL_DEPTH_32F, 3);
    IplImage *difference = nullptr;

    CvScalar green = cvScalar(0.0, 255.0, 0.0);

    while (true) {
        IplImage *colorImage = cvQueryFrame(this->capture);
        // Remove false positives
        cvSmooth(colorImage, colorImage, CV_GAUSSIAN, 3, 0);
        IplImage *temp;
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
        cvFindContours(greyImage, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        // For all contours compute the area
        while (contours) {
            currentSurface += cvContourArea(contours);
            CvRect boundingRect = cvBoundingRect(contours);
            CvPoint point1 = cvPoint(boundingRect.x, boundingRect.y);
            CvPoint point2 = cvPoint(boundingRect.x + boundingRect.width, boundingRect.y + boundingRect.height);
            cvRectangle(colorImage, point1, point2, green, 2);
            contours = contours->h_next;
        }

        // Calculate the average of contour area on the total size
        int average = (currentSurface * 100) / surface;
        if (average > this->ceil) {
            std::cout << "Something is moving..." << std::endl;
        }
        // Put back the current surface to 0
        currentSurface = 0;
        // display image
        cvShowImage(window::kTarget.c_str(), colorImage);
        // exit if ESC button pressed
        int c = cvWaitKey(1);
        if (c == 27) {
            break;
        }
    }

    cvReleaseImage(&greyImage);
    cvReleaseImage(&movingAverage);
    if (difference) {
        cvReleaseImage(&difference);
    }
}

#endif //VISIONARY_MOTION_DETECTOR_H
