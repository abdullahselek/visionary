//
// Created by Abdullah Selek on 15/06/2017.
//

#ifndef VISIONARY_EYE_DETECTOR_H
#define VISIONARY_EYE_DETECTOR_H

#include <string>

class EyeDetector {

public:
    EyeDetector(std::string cascadePath);
    ~EyeDetector();

private:
    std::string cascadePath;

};

inline EyeDetector::EyeDetector(std::string cascadePath) {
    this->cascadePath = cascadePath;
}

inline EyeDetector::~EyeDetector() {

}

#endif //VISIONARY_EYE_DETECTOR_H
