// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
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
#include "CinderImGui.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <string>
#include "randomizedSVD.h"


namespace myapp {

    using namespace cv;

    using cinder::Color;
    using cinder::ColorA;
    using cinder::Rectf;
    using cinder::TextBox;
    using cinder::app::KeyEvent;
    using std::string;
    const char kNormalFont[] = "Arial";
    void PrintText(const string &text, const Color &color, const cinder::ivec2 &size,
                   const cinder::vec2 &loc);
    float slide = 0.f;
    string file;
    bool display_image = false;
    bool rewrite_image = false;
    bool make_new_file = false;
    bool use_compression = false;
    MyApp::MyApp() {

        ImGui::initialize();
        Mat image_cv = imread("/Users/sarishdeotale/Downloads/cinder_0.9.2_mac/my-projects/final-project-notSarish/assets/apple.jpeg", IMREAD_GRAYSCALE);
        Eigen::MatrixXf image_eigen;


        cv2eigen(image_cv, image_eigen);

        mylibrary::CompressImage(image_cv, .99);

    }

    void MyApp::setup() {
      //  draw();
    }

    void MyApp::update() {
        cinder::gl::clear( Color( 0, 0, 0 ) );
       // ui::ScopedWindow window;
        //ui::ScopedWindow window("Grayscale Image Sharpening", ImGuiWindowFlags_None);
        /*if (ImGui::Button("Grayscale Image")) {
            display_image = !display_image;
        }
        if (display_image) {
            ui::ScopedWindow window("Grayscale Image Sharpening", ImGuiWindowFlags_None);
            ui::Text("Select How Sharp You Want Your Image");
            ui::SliderFloat("slide", &slide, 0.f, 2.f);
            string file_name = "";
            if(ui::InputText("Enter your image", &file_name)) {
               // if valid file
               if (file_name.size() != 0) {
                   file = file_name;

                  // std::cout<< file << std::endl;
               }
              //  std::cout<< "new"  << file << std::endl;

            }
            if (file.size() != 0) {
                if (!mylibrary::IsValidFile(file)) {
                    ui::Text("Invalid File");
                } else {
                    mylibrary::SharpenImage(file, slide, rewrite_image, make_new_file, use_compression);
                }
            }
            //ui::Check
            ui::Checkbox("Compress Image", &use_compression);
            rewrite_image = ui::Button("Rewrite File");
            make_new_file = ui::Button("Make New File");

        }
*/

        //ImGui::SliderInt("slide", &slide, 0, 100);
    }

    void MyApp::draw() {
        DrawMenu();


      //  int slid = 0;
     //   ui::SliderInt("slidee", &slid, 0, 100);

    }

    void MyApp::DrawMenu() {
        //const string app_name = "Image Altering App";
        const Color color = Color::white();
        const cinder::ivec2 size = {500, 50};
        const cinder::vec2 center = getWindowCenter();

        PrintText("Image Altering App", color, size, {center.x, 100});

    }

    void MyApp::keyDown(KeyEvent event) {}

    //template <typename C>
    void PrintText(const string &text, const Color &color, const cinder::ivec2 &size,
                   const cinder::vec2 &loc) {
        cinder::gl::color(color);

        auto box = TextBox()
                .alignment(TextBox::CENTER)
                .font(cinder::Font(kNormalFont, 30))
                .size(size)
                .color(color)
                .backgroundColor(ColorA(0, 0, 0, 0))
                .text(text);

        const auto box_size = box.getSize();
        const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
        const auto surface = box.render();
        const auto texture = cinder::gl::Texture::create(surface);
        cinder::gl::draw(texture, locp);
    }
}