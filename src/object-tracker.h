//
// Created by Abdullah Selek on 20/06/2017.
//

#ifndef VISIONARY_OBJECT_TRACKER_H
#define VISIONARY_OBJECT_TRACKER_H

#include "opencv2/opencv.hpp"
#include "opencv2/tracking.hpp"
#include "constants.h"

class ObjectTracker {

public:
    ObjectTracker();
    ObjectTracker(tracker::type trackerType);
    ~ObjectTracker();

private:
    cv::Ptr<cv::Tracker> tracker;

};

inline ObjectTracker::ObjectTracker() {

}

inline ObjectTracker::ObjectTracker(tracker::type trackerType) {
    tracker = cv::Tracker::create(tracker::getCharForEnum(trackerType));
}

inline ObjectTracker::~ObjectTracker() {

}

#endif //VISIONARY_OBJECT_TRACKER_H
