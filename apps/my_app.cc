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
//    float slide = 0.f;
//    string file;
//    double compression;
//    bool display_image = false;
//    bool compress_image = false;
//    bool rewrite_image = false;
//    bool make_new_file = false;
//    bool use_compression = false;
//    bool exit_image_app = false;
//    bool exit_compression_app = false;
//    bool enter_compress = false;
    MyApp::MyApp() {

        ImGui::initialize();

    }

    void MyApp::setup() {
      //  draw();
    }

    void MyApp::update() {

        cinder::gl::clear( Color( 0, 0, 0 ) );

        if (ImGui::Button("Grayscale Image Sharpening")) {
            display_image = !display_image;
        } else if (ImGui::Button("Compress Image")) {
            compress_image = !compress_image;
        }

        if (display_image) {

            ui::ScopedWindow window("Grayscale Image Sharpening", ImGuiWindowFlags_None);
            ui::Text("Select How Sharp You Want Your Image");
            ui::SliderFloat("slide", &slide, 0.f, 2.f);

            string file_name = "";
            if(ui::InputText("Enter your image", &file_name)) {

               if (file_name.size() != 0) {
                   file = file_name;
               }

            }

            if (file.size() != 0) {

                if (!mylibrary::IsValidFile(file)) {
                    ui::Text("Invalid File");
                } else {
                    mylibrary::SharpenImage(file, slide, rewrite_image, make_new_file);
                }

            }
            if (exit_image_app) {

                display_image = false;
                exit_image_app = false;

            }

            rewrite_image = ui::Button("Rewrite File");
            make_new_file = ui::Button("Make New File");
            exit_image_app = ui::Button("Exit");

        } else if (compress_image) {

            ui::ScopedWindow window("Compress Image", ImGuiWindowFlags_None);
            ui::Text("Choose How Compressed You Want Your Image (as a double between 0 and 1)");


            ui::InputDouble("Enter Compression", &compression);

            ui::InputText("Enter Your Image", &file);


            if (enter_compress || rewrite_image || make_new_file) {
                if (!mylibrary::IsValidFile(file)) {
                    invalid_file = true;
                    //ui::Text("Invalid File");
                } else if (!mylibrary::CompressImage(file, compression, rewrite_image, make_new_file)) {
                    invalid_compression = true;
                    // ui::Text("Invalid Compression Value");
                } else {
                    invalid_file = false;
                    invalid_compression = false;
                }

            }

            if (invalid_file) {
                ui::Text("Invalid File");
            } else if (invalid_compression) {
                ui::Text("Invalid Compression Value");
            }

            if (exit_compression_app) {
                compress_image = false;
                exit_compression_app = false;
            }

            enter_compress = ui::Button("Enter");
            rewrite_image = ui::Button("Rewrite File");
            make_new_file = ui::Button("Make New File");
            exit_compression_app = ui::Button("Exit");
            
        }

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