# visionary

[![Build Status](https://travis-ci.org/abdullahselek/visionary.svg?branch=master)](https://travis-ci.org/abdullahselek/visionary)

Various types of detection implementations with OpenCV and C++.

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
FaceDetector faceDetector("YOUR_CASCADE_PATH", source::type::camera, nullptr);
faceDetector.run();
```

To detect face from given local video

```
FaceDetector faceDetector("YOUR_CASCADE_PATH", source::type::video, "YOUR_VIDEO_PATH");
faceDetector.run();
```

To detect face from given image

```
FaceDetector faceDetector("YOUR_CASCADE_PATH", source::type::image, "YOUR_IMAGE_PATH");
faceDetector.run();
```

### Face & Eye Detection

To detect eye and face from given image

```
EyeDetector eyeDetector;
eyeDetector.setEyeCascadePath("YOUR_EYE_CASCADE_PATH");
eyeDetector.setFaceCascadePath("YOUR_FACE_CASCADE_PATH");
eyeDetector.setSourcePath("YOUR_IMAGE_PATH");
eyeDetector.setSourceType(source::type::image);
eyeDetector.run();
```

To detect eye and face from camera

```
EyeDetector eyeDetector("YOUR_EYE_CASCADE_PATH",
                        "YOUR_FACE_CASCADE_PATH",
                        source::type::camera,
                        nullptr);
eyeDetector.run();
```

To detect eye and face from given local video

```
EyeDetector eyeDetector("YOUR_EYE_CASCADE_PATH",
                        "YOUR_FACE_CASCADE_PATH",
                        source::type::video,
                        "YOUR_VIDEO_PATH");
eyeDetector.run();
```

## Sample Videos & Images

### Videos

[Motion Detection](https://youtu.be/xgXo35C3IQE)<br />
[Face Detection](https://youtu.be/bf5NtpbNbYg)<br />
[Face & Eyes Detection](https://youtu.be/GFfjjkKZwhs)<br />

### Images

![Face Detection](/samples/face_detection.png)<br />
![Face & Eyes Detection](/samples/face_eye_detection.png)

### NOTE

OpenCV should be installed to your computer before running, take a look at .travis.yml file for sample installation for macOS and Linux.
