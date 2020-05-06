// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <Eigen/Dense>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/eigen.hpp"



/*
 * deblurring is a subset of inverse problems
 * in other words, the representation of blur can be seen through a simple linear equation
 * blurry_image = blur(actual image) + noise
 */

namespace mylibrary {
using namespace cv;
using namespace Eigen;
//using namespace Eigen;
bool IsValidFile(const std::string &kFileName);

void SharpenImage(const std::string &kFileName, const double kConstant, const bool kRewriteImage, const bool kMakeNewFile,
        const bool compress_image);

void DenoiseImage(Mat &image_cv);

std::string CopyFile(const std::string &kFileName);

void CompressImage(Mat &image_cv, const double kCompression);






}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
