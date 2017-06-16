#include "src/motion-detector.h"
#include "src/face-detector.h"
#include "src/eye-detector.h"
#include "test/utils.h"

void detectMotion() {
    MotionDetector motionDetector;
    motionDetector.setCeil(15);
    motionDetector.openCamera();
    motionDetector.run();
}

void detectFaceInVideo(const char *currentPath) {
    const char *cascadePath = "/haarcascades/haarcascade_frontalface_alt2.xml";
    std::__1::string fullCascadePath(currentPath);
    Utils::replaceStringInPlace(fullCascadePath, "/src", "");
    fullCascadePath += cascadePath;

    FaceDetector faceDetector(fullCascadePath.c_str(), source::video, nullptr);
    faceDetector.openCamera();
    faceDetector.detectInVideo();
}

void detectFaceInImage(const char *currentPath) {
    const char *cascadePath = "/haarcascades/haarcascade_frontalface_alt2.xml";
    std::__1::string fullCascadePath(currentPath);
    Utils::replaceStringInPlace(fullCascadePath, "/src", "");
    fullCascadePath += cascadePath;

    const char *imagePath = "/resources/5083377.png";
    std::__1::string fullImagePath(currentPath);
    Utils::replaceStringInPlace(fullImagePath, "/src", "");
    fullImagePath += imagePath;

    FaceDetector faceDetector(fullCascadePath.c_str(), source::image, fullImagePath.c_str());
    faceDetector.detectInImage();
}

void detectFaceEyeInImage(const char *currentPath) {
    const char *eyeCascadePath = "/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
    std::__1::string fullEyeCascadePath(currentPath);
    Utils::replaceStringInPlace(fullEyeCascadePath, "/src", "");
    fullEyeCascadePath += eyeCascadePath;

    const char *faceCascadePath = "/haarcascades/haarcascade_frontalface_alt2.xml";
    std::__1::string fullFaceCascadePath(currentPath);
    Utils::replaceStringInPlace(fullFaceCascadePath, "/src", "");
    fullFaceCascadePath += faceCascadePath;

    const char *imagePath = "/resources/5083377.png";
    std::__1::string fullImagePath(currentPath);
    Utils::replaceStringInPlace(fullImagePath, "/src", "");
    fullImagePath += imagePath;

    EyeDetector eyeDetector(fullImagePath.c_str());
    eyeDetector.setEyeCascadePath(fullEyeCascadePath.c_str());
    eyeDetector.setFaceCascadePath(fullFaceCascadePath.c_str());
    eyeDetector.prepare();
    eyeDetector.detectInImage();
}

void detectFaceEyeInVideo(const char *currentPath) {
    const char *eyeCascadePath = "/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
    std::__1::string fullEyeCascadePath(currentPath);
    Utils::replaceStringInPlace(fullEyeCascadePath, "/src", "");
    fullEyeCascadePath += eyeCascadePath;

    const char *faceCascadePath = "/haarcascades/haarcascade_frontalface_alt2.xml";
    std::__1::string fullFaceCascadePath(currentPath);
    Utils::replaceStringInPlace(fullFaceCascadePath, "/src", "");
    fullFaceCascadePath += faceCascadePath;

    const char *imagePath = "/resources/5083377.png";
    std::__1::string fullImagePath(currentPath);
    Utils::replaceStringInPlace(fullImagePath, "/src", "");
    fullImagePath += imagePath;

    EyeDetector eyeDetector(fullEyeCascadePath.c_str(),
                            fullFaceCascadePath.c_str(),
                            nullptr);
    eyeDetector.prepare();
    eyeDetector.detectInVideo();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 0;
    } else {
        const char *currentPath = Utils::currentDirectory();

        std::string run = argv[1];
        if (run == "m") {
            detectMotion();
        } else if (run == "fv") {
            detectFaceInVideo(currentPath);
        } else if (run == "fi") {
            detectFaceInImage(currentPath);
        } else if (run == "ev") {
            detectFaceEyeInVideo(currentPath);
        } else {
            detectFaceEyeInImage(currentPath);
        }
    }

    return 0;
}
