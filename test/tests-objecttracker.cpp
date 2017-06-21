//
// Created by Abdullah Selek on 21/06/2017.
//

#include "gtest/gtest.h"
#include "../src/object-tracker.h"

class ObjectTrackerTests : public ::testing::Test {

protected:
    virtual ~ObjectTrackerTests() {

    }

    virtual void SetUp() {

    }

    virtual void TearDown() {

    }

public:
    ObjectTrackerTests() {

    }
    ObjectTracker *objectTracker;

};

TEST_F(ObjectTrackerTests, Instantiate) {
    objectTracker = new ObjectTracker();
    EXPECT_TRUE(objectTracker != nullptr);
    delete objectTracker;
}

TEST_F(ObjectTrackerTests, InstantiateWithType) {
    objectTracker = new ObjectTracker(tracker::type::mil, source::type::video, "");
    EXPECT_TRUE(objectTracker != nullptr);
    delete objectTracker;
}
