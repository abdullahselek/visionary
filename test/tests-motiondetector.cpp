//
// Created by Abdullah Selek on 07/06/2017.
//

#include "gtest/gtest.h"
#include "../src/motion-detector.h"

class MotionDetectorTests : public ::testing::Test {

protected:
    virtual ~MotionDetectorTests() {

    }

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }

public:
    MotionDetectorTests() {

    }
    MotionDetector *motionDetector;

};

TEST_F(MotionDetectorTests, Initiate) {
    motionDetector = new MotionDetector("", 15);
    EXPECT_TRUE(motionDetector != nullptr);
    EXPECT_TRUE(motionDetector->getVideoPath().empty());
}

TEST_F(MotionDetectorTests, InitiateWithVideoPath) {
    const char *videoPath = "/Users/admin/video.mp4";
    motionDetector = new MotionDetector(videoPath, 15);
    EXPECT_TRUE(motionDetector != nullptr);
    EXPECT_FALSE(motionDetector->getVideoPath().empty());
}

TEST_F(MotionDetectorTests, InitiateWithCeil) {
    motionDetector = new MotionDetector(15);
    EXPECT_TRUE(motionDetector != nullptr);
}

TEST_F(MotionDetectorTests, Capture) {
    motionDetector = new MotionDetector(15);
    EXPECT_FALSE(motionDetector->getCapture() == nullptr);
}

TEST_F(MotionDetectorTests, CaptureAfterOpenCamera) {
    motionDetector = new MotionDetector(15);
    motionDetector->openCamera();
    EXPECT_FALSE(motionDetector->getCapture() == nullptr);
}
