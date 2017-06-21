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
    ObjectTracker(tracker::type trackerType,
                  source::type sourceType,
                  const char *videoPath);
    ~ObjectTracker();

private:
    cv::Ptr<cv::Tracker> tracker;
    const char *videoPath;

};

inline ObjectTracker::ObjectTracker() {

}

inline ObjectTracker::ObjectTracker(tracker::type trackerType,
                                    source::type sourceType,
                                    const char *videoPath) {
    assert(sourceType != source::type::image && "Unsupported type for object tracker!");
    this->tracker = cv::Tracker::create(tracker::getCharForEnum(trackerType));
    this->videoPath = videoPath;
}

inline ObjectTracker::~ObjectTracker() {

}

#endif //VISIONARY_OBJECT_TRACKER_H
