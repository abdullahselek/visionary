//
// Created by Abdullah Selek on 15/06/2017.
//

#include "gtest/gtest.h"
#include "../src/eye-detector.h"
#include "utils.h"

class EyeDetectorTests : public ::testing::Test {

protected:
    virtual ~EyeDetectorTests() {

    }

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }

public:
    EyeDetectorTests() {

    }
    EyeDetector *eyeDetector;

};

TEST_F(EyeDetectorTests, Initiate) {
    eyeDetector = new EyeDetector();
    EXPECT_TRUE(eyeDetector != nullptr);
    delete eyeDetector;
}

TEST_F(EyeDetectorTests, InitiateWithCascadeAndVideoPath) {
    eyeDetector = new EyeDetector("", "", "");
    EXPECT_TRUE(eyeDetector != nullptr);
    delete eyeDetector;
}

TEST_F(EyeDetectorTests, InitiateWithImagePath) {
    eyeDetector = new EyeDetector("");
    EXPECT_TRUE(eyeDetector != nullptr);
    delete eyeDetector;
}

TEST_F(EyeDetectorTests, SetEyeCascadePath) {
    eyeDetector = new EyeDetector();
    EXPECT_TRUE(eyeDetector != nullptr);
    eyeDetector->setEyeCascadePath("");
    delete eyeDetector;
}

TEST_F(EyeDetectorTests, Prepare) {
    eyeDetector = new EyeDetector();
    EXPECT_TRUE(eyeDetector != nullptr);

    const char *currentPath = Utils::currentDirectory();
    const char *eyeCascadePath = "/haarcascades/haarcascade_eye.xml";
    std::string fullEyeCascadePath(currentPath);
    Utils::replaceStringInPlace(fullEyeCascadePath, "/test", "");
    fullEyeCascadePath += eyeCascadePath;

    const char *faceCascadePath = "/haarcascades/haarcascade_frontalface_alt2.xml";
    std::string fullFaceCascadePath(currentPath);
    Utils::replaceStringInPlace(fullFaceCascadePath, "/test", "");
    fullFaceCascadePath += faceCascadePath;

    eyeDetector->setEyeCascadePath(fullEyeCascadePath.c_str());
    eyeDetector->setFaceCascadePath(fullFaceCascadePath.c_str());
    EXPECT_TRUE(eyeDetector->prepare());
}
