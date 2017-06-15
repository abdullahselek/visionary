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
    eyeDetector = new EyeDetector("");
    EXPECT_TRUE(eyeDetector != nullptr);
    delete eyeDetector;
}
