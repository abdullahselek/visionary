//
// Created by Abdullah Selek on 20/06/2017.
//

#ifndef VISIONARY_OBJECT_TRACKER_H
#define VISIONARY_OBJECT_TRACKER_H

#include "opencv2/opencv.hpp"
#include "opencv2/tracking.hpp"
#include "constants.h"
#include "utility.h"

class ObjectTracker {

public:
    ObjectTracker();
    ObjectTracker(tracker::type trackerType,
                  source::type sourceType,
                  const char *videoPath);
    ~ObjectTracker();
    void run(cv::Rect2d boundingBox);

private:
    cv::Tracker *tracker;
    const char *sourcePath;
    cv::VideoCapture capture;
    source::type sourceType;

    inline void openCamera();
    inline void trackInVideo(cv::Rect2d boundingBox);
    inline void trackInCamera(cv::Rect2d boundingBox);

};

inline ObjectTracker::ObjectTracker() {

}

inline ObjectTracker::ObjectTracker(tracker::type trackerType,
                                    source::type sourceType,
                                    const char *sourcePath) {
    assert(sourceType != source::type::image && "Unsupported type for object tracker!");
    this->sourcePath = sourcePath;
    this->sourceType = sourceType;
}

inline ObjectTracker::~ObjectTracker() {

}

inline void ObjectTracker::openCamera() {
    if (this->sourcePath) {
        this->capture = cv::VideoCapture(cv::String(this->sourcePath));
    } else {
        this->capture = cv::VideoCapture(cv::VideoCaptureAPIs::CAP_ANY);
    }
    cv::namedWindow(window::kTarget, 1);
}

inline void ObjectTracker::trackInVideo(cv::Rect2d boundingBox) {
    // load video
    openCamera();

    // colors for drawing
    CvScalar green = cvScalar(0.0, 255.0, 0.0);

    // Check video is open
    if(!this->capture.isOpened()) {
        std::cout << "Could not read video file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Read first frame.
    cv::Mat frame;
    this->capture.read(frame);

    // Initialize tracker with first frame and bounding box
    tracker->init(frame, boundingBox);

    while(this->capture.read(frame)) {
        // Update tracking results
        tracker->update(frame, boundingBox);
        // Draw bounding box
        rectangle(frame, boundingBox, green, 2, 1);
        // Display result
        imshow(window::kTarget, frame);
        int c = cv::waitKey(1);
        if (c == 27) {
            break;
        }
    }
}

inline void ObjectTracker::trackInCamera(cv::Rect2d boundingBox) {
    // open camera
    openCamera();

    // colors for drawing
    CvScalar green = cvScalar(0.0, 255.0, 0.0);

    // Check video is open
    if(!this->capture.isOpened()) {
        std::cout << "Could not read from camera!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Read first frame.
    cv::Mat frame;
    this->capture.read(frame);

    // Initialize tracker with first frame and bounding box
    tracker->init(frame, boundingBox);

    while (true) {
        this->capture.read(frame);
        // Update tracking results
        tracker->update(frame, boundingBox);
        // Draw bounding box
        rectangle(frame, boundingBox, green, 2, 1);
        // Display result
        imshow(window::kTarget, frame);
        int c = cv::waitKey(1);
        if (c == 27) {
            break;
        }
    }
}

inline void ObjectTracker::run(cv::Rect2d boundingBox) {
    switch (this->sourceType) {
        case source::type::video:
            this->trackInVideo(boundingBox);
            break;
        case source::type::camera:
            this->trackInCamera(boundingBox);
            break;
        case source::type::image:
            break;
    }
}

#endif //VISIONARY_OBJECT_TRACKER_H
