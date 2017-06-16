#include "src/motion-detector.h"
#include "src/face-detector.h"
#include "src/eye-detector.h"
#include "test/utils.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 0;
    } else {
        const char *currentPath = Utils::currentDirectory();

        std::string run = argv[1];
        if (run == "m") {
            MotionDetector motionDetector;
            motionDetector.setCeil(15);
            motionDetector.openCamera();
            motionDetector.run();
        } else if (run == "f") {
            const char *cascadePath = "/haarcascades/haarcascade_frontalface_alt2.xml";
            std::string fullCascadePath(currentPath);
            Utils::replaceStringInPlace(fullCascadePath, "/src", "");
            fullCascadePath += cascadePath;

            FaceDetector faceDetector(fullCascadePath.c_str(), nullptr);
            faceDetector.openCamera();
            faceDetector.run();
        } else if (run == "ei") {
            const char *eyeCascadePath = "/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
            std::string fullEyeCascadePath(currentPath);
            Utils::replaceStringInPlace(fullEyeCascadePath, "/src", "");
            fullEyeCascadePath += eyeCascadePath;

            const char *faceCascadePath = "/haarcascades/haarcascade_frontalface_alt2.xml";
            std::string fullFaceCascadePath(currentPath);
            Utils::replaceStringInPlace(fullFaceCascadePath, "/src", "");
            fullFaceCascadePath += faceCascadePath;

            const char *imagePath = "/resources/5083377.png";
            std::string fullImagePath(currentPath);
            Utils::replaceStringInPlace(fullImagePath, "/src", "");
            fullImagePath += imagePath;

            EyeDetector eyeDetector(fullImagePath.c_str());
            eyeDetector.setEyeCascadePath(fullEyeCascadePath.c_str());
            eyeDetector.setFaceCascadePath(fullFaceCascadePath.c_str());
            eyeDetector.prepare();
            eyeDetector.detectInImage();
        } else {
            const char *eyeCascadePath = "/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
            std::string fullEyeCascadePath(currentPath);
            Utils::replaceStringInPlace(fullEyeCascadePath, "/src", "");
            fullEyeCascadePath += eyeCascadePath;

            const char *faceCascadePath = "/haarcascades/haarcascade_frontalface_alt2.xml";
            std::string fullFaceCascadePath(currentPath);
            Utils::replaceStringInPlace(fullFaceCascadePath, "/src", "");
            fullFaceCascadePath += faceCascadePath;

            const char *imagePath = "/resources/5083377.png";
            std::string fullImagePath(currentPath);
            Utils::replaceStringInPlace(fullImagePath, "/src", "");
            fullImagePath += imagePath;

            EyeDetector eyeDetector(fullEyeCascadePath.c_str(),
                                    fullFaceCascadePath.c_str(),
                                    nullptr);
            eyeDetector.prepare();
            eyeDetector.detectInVideo();
        }
    }

    return 0;
}