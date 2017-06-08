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
    motionDetector = new MotionDetector("");
    EXPECT_TRUE(motionDetector != nullptr);
    EXPECT_TRUE(motionDetector->getVideoPath().empty());
}

TEST_F(MotionDetectorTests, InitiateWithVideoPath) {
    std::string videoPath("/Users/admin/video.mp4");
    motionDetector = new MotionDetector(videoPath);
    EXPECT_TRUE(motionDetector != nullptr);
    EXPECT_FALSE(motionDetector->getVideoPath().empty());
}

TEST_F(MotionDetectorTests, InitiateWithCeil) {
    motionDetector = new MotionDetector(15);
    EXPECT_TRUE(motionDetector != nullptr);
}

TEST_F(MotionDetectorTests, OpenCamera) {
    motionDetector = new MotionDetector(15);
    EXPECT_FALSE(motionDetector->getCapture() == nullptr);
}
