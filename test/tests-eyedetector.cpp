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
    eyeDetector = new EyeDetector("", "");
    EXPECT_TRUE(eyeDetector != nullptr);
    delete eyeDetector;
}

TEST_F(EyeDetectorTests, InitiateWithImagePath) {
    eyeDetector = new EyeDetector("");
    EXPECT_TRUE(eyeDetector != nullptr);
    delete eyeDetector;
}

TEST_F(EyeDetectorTests, SetCascadePath) {
    eyeDetector = new EyeDetector();
    EXPECT_TRUE(eyeDetector != nullptr);
    eyeDetector->setCascadePath("");
    delete eyeDetector;
}

TEST_F(EyeDetectorTests, Prepare) {
    eyeDetector = new EyeDetector();
    EXPECT_TRUE(eyeDetector != nullptr);

    const char *currentPath = Utils::currentDirectory();
    const char *cascadePath = "/haarcascades/haarcascade_eye.xml";
    std::string fullCascadePath(currentPath);
    Utils::replaceStringInPlace(fullCascadePath, "/test", "");
    fullCascadePath += cascadePath;

    eyeDetector->setCascadePath(fullCascadePath.c_str());
    EXPECT_TRUE(eyeDetector->prepare());
}
