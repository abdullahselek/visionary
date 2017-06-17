//
// Created by Selek, Abdullah on 16.06.17.
//

#ifndef VISIONARY_UTILITY_H
#define VISIONARY_UTILITY_H

#include "opencv2/opencv.hpp"

namespace utility {

    inline CvCapture * createCapture(const char * videoPath) {
        if (videoPath != nullptr) {
            return cvCreateFileCapture(videoPath);
        } else {
            return cvCreateCameraCapture(CV_CAP_ANY);
        }
    }

}

namespace visionary {

    inline void drawRectangle(std::vector<cv::Rect>::iterator it, IplImage *image, CvScalar scalarColor) {
        // create points
        cv::Rect rect = *it;
        CvPoint point1;
        point1.x = rect.x;
        point1.y = rect.y;
        CvPoint point2;
        point2.x = rect.x + rect.width;
        point2.y = rect.y + rect.height;
        // draw rectangle for the face
        cvRectangle(image, point1, point2, scalarColor, 2);
    }

    inline void drawRectangle(CvSeq *contours, IplImage *image, CvScalar scalarColor) {
        CvRect boundingRect = cvBoundingRect(contours);
        CvPoint point1 = cvPoint(boundingRect.x, boundingRect.y);
        CvPoint point2 = cvPoint(boundingRect.x + boundingRect.width, boundingRect.y + boundingRect.height);
        cvRectangle(image, point1, point2, scalarColor, 2);
    }

    inline void setCaptureFrame(CvCapture *capture, double width, double height) {
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, width);
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, height);
    }

}

#endif //VISIONARY_UTILITY_H
