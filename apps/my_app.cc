// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <Eigen/Dense>

#include "Eigen/Core"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/eigen.hpp"
#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "mylibrary/model.h"
#include "opencv2/photo/photo.hpp"
using namespace cv;

namespace myapp {


using cinder::app::KeyEvent;



MyApp::MyApp() {
    mylibrary::SharpenImage("/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/blurryimage.jpg");

}

void MyApp::setup() { }

void MyApp::update() { }

void MyApp::draw() { }

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp


