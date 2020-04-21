// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <Eigen/Dense>
#include "CinderOpenCV.h"
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
namespace myapp {

using cinder::app::KeyEvent;
using namespace cv;

MyApp::MyApp() {

    Mat A;
    std::string file_name = "/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/blurryimage.jpg";
    A = imread(file_name, CV_LOAD_IMAGE_GRAYSCALE);
   // std::cout << A;
}

void MyApp::setup() { }

void MyApp::update() { }

void MyApp::draw() { }

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
