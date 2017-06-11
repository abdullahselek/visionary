//
// Created by Abdullah Selek on 10/06/2017.
//

#ifndef VISIONARY_MOCK_MOTION_DETECTOR_H
#define VISIONARY_MOCK_MOTION_DETECTOR_H

#include "../src/motion-detector.h"
#include "gmock/gmock.h"

class MockMotionDetector: public MotionDetector {

public:
    MOCK_METHOD0(createCapture, CvCapture * ());

};

#endif //VISIONARY_MOCK_MOTION_DETECTOR_H
