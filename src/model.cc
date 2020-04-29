// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/model.h>
#include <Eigen/Dense>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/photo/photo.hpp"


namespace mylibrary {
    void SharpenImage(const std::string &kFileName, const double cons) {
        Mat image_cv = imread(kFileName, IMREAD_GRAYSCALE);
        Mat original = imread(kFileName, IMREAD_GRAYSCALE);
        DenoiseImage(image_cv);
        //imshow("No Noise Image", image_cv);
        Mat laplacian;
        Laplacian(image_cv, laplacian, CV_16S, 1, 1, 0, BORDER_DEFAULT);
        Mat dst;
        convertScaleAbs(laplacian, dst);
       // imshow("Laplacian", dst);
        Mat show = original - cons*dst;
      //  fastNlMeansDenoising(show, show, 3, 7, 21);
        imshow("Sharpen", show);
    }

    void DenoiseImage(Mat &image_cv) {
        //blur(image_cv, image_cv, Size(3,3), Point(-1,-1), BORDER_DEFAULT);
       GaussianBlur( image_cv, image_cv, Size(3,3), 0, 0, BORDER_DEFAULT );
        //medianBlur(image_cv, image_cv, 5);
    }


}  // namespace mylibrary
