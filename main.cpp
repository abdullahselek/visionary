#include "src/motion-detector.h"

int main() {
    MotionDetector motionDetector;
    motionDetector.setCeil(15);
    motionDetector.openCamera();
    motionDetector.run();

    return 0;
}