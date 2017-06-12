//
// Created by Abdullah Selek on 07/06/2017.
//

#include "gtest/gtest.h"
#include "opencv2/opencv.hpp"
#include "../src/motion-detector.h"
#include "mock-motion-detector.h"
#include "utils.h"

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
    EXPECT_EQ(motionDetector->getVideoPath(), "");
    delete motionDetector;
}

TEST_F(MotionDetectorTests, InitiateWithVideoPath) {
    const char *videoPath = "/Users/admin/video.mp4";
    motionDetector = new MotionDetector(videoPath, 15);
    EXPECT_TRUE(motionDetector != nullptr);
    EXPECT_EQ(motionDetector->getVideoPath(), videoPath);
    delete motionDetector;
}

TEST_F(MotionDetectorTests, InitiateWithCeil) {
    motionDetector = new MotionDetector(15);
    EXPECT_TRUE(motionDetector != nullptr);
    delete motionDetector;
}

TEST_F(MotionDetectorTests, CreateCapture) {
    MockMotionDetector mockMotionDetector;
    const char *currentPath = currentDirectory();
    const char *videoPath = "/resources/SampleVideo.mp4";
    std::string fullPath(currentPath);
    replaceStringInPlace(fullPath, "/test", "");
    fullPath += videoPath;
    std::cout << "Video File Path " << fullPath << std::endl;
    EXPECT_CALL(mockMotionDetector, createCapture())
            .Times(1)
            .WillOnce(testing::Return(cvCreateFileCapture(fullPath.c_str())));
    CvCapture *capture = mockMotionDetector.createCapture();
    EXPECT_TRUE(capture != nullptr);
}

TEST_F(MotionDetectorTests, OpenCamera) {
    const char *currentPath = currentDirectory();
    const char *videoPath = "/resources/SampleVideo.mp4";
    std::string fullPath(currentPath);
    replaceStringInPlace(fullPath, "/test", "");
    fullPath += videoPath;
    std::cout << "Video File Path " << fullPath << std::endl;
    motionDetector = new MotionDetector(fullPath.c_str(), 15);
    motionDetector->openCamera();
    EXPECT_TRUE(motionDetector->getCapture() != nullptr);
}
