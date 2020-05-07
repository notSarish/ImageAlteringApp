// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>


namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void DrawMenu();
  void keyDown(cinder::app::KeyEvent) override;
    float slide = 0.f;
    std::string file;
    double compression;
    bool display_image = false;
    bool compress_image = false;
    bool rewrite_image = false;
    bool make_new_file = false;
    bool use_compression = false;
    bool exit_image_app = false;
    bool exit_compression_app = false;
    bool enter_compress = false;
    bool invalid_file = false;
    bool invalid_compression = false;

 private:


};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
