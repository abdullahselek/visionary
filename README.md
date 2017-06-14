# visionary

[![Build Status](https://travis-ci.org/abdullahselek/visionary.svg?branch=master)](https://travis-ci.org/abdullahselek/visionary)

Motion and face detection implementation with OpenCV and C++.

## Building Repository

To build the repository you need CMake. You can download from [here](https://cmake.org/download/).
You can create a shortcut ```cmake``` command for macOS as below

```
sudo mkdir -p /usr/local/bin
sudo /Applications/CMake.app/Contents/bin/cmake-gui --install=/usr/local/bin
```

After cloning repository to your own local machine go to project root folder and run

```
cmake .
```

and then

```
cmake --build .
```

to run unit tests for UNIX machines

```
cd test
./visionary-test --gtest_color=yes
```

## Sample Usage

### Motion-Detection

To detect motions from camera

```
MotionDetector motionDetector;
motionDetector.setCeil(15);
motionDetector.openCamera();
motionDetector.run();
```

To detect motions from given local video

```
MotionDetector motionDetector;
motionDetector.setCeil(15);
motionDetector.setVideoPath("YOUR_VIDEO_PATH");
motionDetector.openCamera();
motionDetector.run();
```

### Face-Detection

To detect face from camera

```
FaceDetector faceDetector("YOUR_CASCADE_PATH", nullptr);
faceDetector.openCamera();
faceDetector.run();
```

To detect face from given local video

```
FaceDetector faceDetector("YOUR_CASCADE_PATH", "YOUR_VIDEO_PATH");
faceDetector.openCamera();
faceDetector.run();
```

### NOTE

OpenCV should be installed to your computer before running, take a look at .travis.yml file for sample installation for macOS and Linux.
