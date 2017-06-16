//
// Created by Selek, Abdullah on 14.06.17.
//

#include "gtest/gtest.h"
#include "../src/face-detector.h"
#include "utils.h"

class FaceDetectorTests: public ::testing::Test {

protected:
    virtual ~FaceDetectorTests() {

    }

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }

public:
    FaceDetectorTests() {

    }
    FaceDetector *faceDetector;

};

TEST_F(FaceDetectorTests, Instantiate) {
    faceDetector = new FaceDetector();
    EXPECT_TRUE(faceDetector != nullptr);
    delete faceDetector;
}

TEST_F(FaceDetectorTests, InstantiateWithParameters) {
    const char *currentPath = Utils::currentDirectory();

    const char *cascadePath = "/haarcascades/haarcascade_profileface.xml";
    std::string fullCascadePath(currentPath);
    Utils::replaceStringInPlace(fullCascadePath, "/test", "");
    fullCascadePath += cascadePath;

    const char *videoPath = "/resources/SampleVideo.mp4";
    std::string fullVideoPath(currentPath);
    Utils::replaceStringInPlace(fullVideoPath, "/test", "");
    fullVideoPath += videoPath;

    faceDetector = new FaceDetector(fullVideoPath, source::type::video, fullCascadePath.c_str());
    EXPECT_TRUE(faceDetector != nullptr);
    delete faceDetector;
}
