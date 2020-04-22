// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <Eigen/Dense>

namespace myapp {

using cinder::app::KeyEvent;


MyApp::MyApp() {
    using Eigen::MatrixXd;


    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    
    std::cout << m << std::endl;

}

void MyApp::setup() { }

void MyApp::update() { }

void MyApp::draw() { }

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
