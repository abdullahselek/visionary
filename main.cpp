#include "src/motion-detector.h"
#include "src/face-detector.h"
#include "src/eye-detector.h"

void detectMotion() {
    MotionDetector motionDetector;
    motionDetector.setCeil(15);
    motionDetector.openCamera();
    motionDetector.run();
}

void detectFaceInVideo(const char *currentPath) {
    const char *cascadePath = "/haarcascades/haarcascade_frontalface_alt2.xml";
    std::string fullCascadePath(currentPath);
    utility::replaceStringInPlace(fullCascadePath, "/src", "");
    fullCascadePath += cascadePath;

    FaceDetector faceDetector(fullCascadePath.c_str(), source::type::camera, nullptr);
    faceDetector.run();
}

void detectFaceInImage(const char *currentPath) {
    const char *cascadePath = "/haarcascades/haarcascade_frontalface_alt2.xml";
    std::string fullCascadePath(currentPath);
    utility::replaceStringInPlace(fullCascadePath, "/src", "");
    fullCascadePath += cascadePath;

    const char *imagePath = "/resources/5083377.png";
    std::string fullImagePath(currentPath);
    utility::replaceStringInPlace(fullImagePath, "/src", "");
    fullImagePath += imagePath;

    FaceDetector faceDetector(fullCascadePath.c_str(), source::type::image, fullImagePath.c_str());
    faceDetector.run();
}

void detectFaceEyeInImage(const char *currentPath) {
    const char *eyeCascadePath = "/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
    std::string fullEyeCascadePath(currentPath);
    utility::replaceStringInPlace(fullEyeCascadePath, "/src", "");
    fullEyeCascadePath += eyeCascadePath;

    const char *faceCascadePath = "/haarcascades/haarcascade_frontalface_alt2.xml";
    std::string fullFaceCascadePath(currentPath);
    utility::replaceStringInPlace(fullFaceCascadePath, "/src", "");
    fullFaceCascadePath += faceCascadePath;

    const char *imagePath = "/resources/5083377.png";
    std::string fullImagePath(currentPath);
    utility::replaceStringInPlace(fullImagePath, "/src", "");
    fullImagePath += imagePath;

    EyeDetector eyeDetector;
    eyeDetector.setEyeCascadePath(fullEyeCascadePath.c_str());
    eyeDetector.setFaceCascadePath(fullFaceCascadePath.c_str());
    eyeDetector.setSourcePath(fullImagePath.c_str());
    eyeDetector.setSourceType(source::type::image);
    eyeDetector.run();
}

void detectFaceEyeInVideo(const char *currentPath) {
    const char *eyeCascadePath = "/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
    std::string fullEyeCascadePath(currentPath);
    utility::replaceStringInPlace(fullEyeCascadePath, "/src", "");
    fullEyeCascadePath += eyeCascadePath;

    const char *faceCascadePath = "/haarcascades/haarcascade_frontalface_alt2.xml";
    std::string fullFaceCascadePath(currentPath);
    utility::replaceStringInPlace(fullFaceCascadePath, "/src", "");
    fullFaceCascadePath += faceCascadePath;

    const char *imagePath = "/resources/5083377.png";
    std::string fullImagePath(currentPath);
    utility::replaceStringInPlace(fullImagePath, "/src", "");
    fullImagePath += imagePath;

    EyeDetector eyeDetector(fullEyeCascadePath.c_str(),
                            fullFaceCascadePath.c_str(),
                            source::type::camera,
                            nullptr);
    eyeDetector.run();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 0;
    } else {
        const char *currentPath = utility::currentDirectory();

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
