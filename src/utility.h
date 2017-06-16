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

    inline void drawRectangleOnFace(std::vector<cv::Rect>::iterator it, IplImage *image, CvScalar scalarScolor) {
        // create points
        cv::Rect rect = *it;
        CvPoint point1;
        point1.x = rect.x;
        point1.y = rect.y;
        CvPoint point2;
        point2.x = rect.x + rect.width;
        point2.y = rect.y + rect.height;
        // draw rectangle for the face
        cvRectangle(image, point1, point2, scalarScolor, 2);
    }

}

#endif //VISIONARY_UTILITY_H
