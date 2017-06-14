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
}

TEST_F(FaceDetectorTests, InstantiateWithCascadePath) {
    const char *currentPath = Utils::currentDirectory();
    const char *cascadePath = "/haarcascades/haarcascade_profileface.xml";
    std::string fullPath(currentPath);
    Utils::replaceStringInPlace(fullPath, "/test", "");
    fullPath += cascadePath;
    faceDetector = new FaceDetector(fullPath.c_str());
    EXPECT_TRUE(faceDetector != nullptr);
}
