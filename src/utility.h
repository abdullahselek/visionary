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

#endif //VISIONARY_UTILITY_H
