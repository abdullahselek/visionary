//
// Created by Selek, Abdullah on 14.06.17.
//

#ifndef VISIONARY_FACE_DETECTOR_H
#define VISIONARY_FACE_DETECTOR_H

class FaceDetector {

public:
    FaceDetector();
    FaceDetector(std::string cascadePath);
    ~FaceDetector();

private:
    std::string cascadePath;

};

inline FaceDetector::FaceDetector() {

}

inline FaceDetector::FaceDetector(std::string cascadePath) {
    this->cascadePath = cascadePath;
}

inline FaceDetector::~FaceDetector() {

}

#endif //VISIONARY_FACE_DETECTOR_H
