#include "src/motion-detector.h"
#include "src/face-detector.h"
#include "test/utils.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 0;
    } else {
        std::string run = argv[1];
        if (run == "motion") {
            MotionDetector motionDetector;
            motionDetector.setCeil(15);
            motionDetector.openCamera();
            motionDetector.run();
        } else  {
            const char *currentPath = Utils::currentDirectory();
            const char *cascadePath = "/haarcascades/haarcascade_frontalface_alt.xml";
            std::string fullCascadePath(currentPath);
            Utils::replaceStringInPlace(fullCascadePath, "/src", "");
            fullCascadePath += cascadePath;

            FaceDetector faceDetector(fullCascadePath.c_str(), nullptr);
            faceDetector.run();
        }
    }

    return 0;
}