// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/model.h>
#include <Eigen/Dense>
#include <fstream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/photo/photo.hpp"


namespace mylibrary {
    bool IsValidFile(const std::string &kFileName) {
        std::ifstream infile(kFileName);
        if (!infile.good()) {
            return false;
        }
        return !(kFileName.substr(kFileName.length() - 4) != "jpeg" && kFileName.substr(kFileName.length() - 3) != "jpg"
                 && kFileName.substr(kFileName.length() - 3) != "png");
    }
    void SharpenImage(const std::string &kFileName, const double cons, const bool rewrite_images, const bool new_file) {
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
        if (rewrite_images) {
            imwrite(kFileName, show);
        } else if (new_file) {
            imwrite(CopyFile(kFileName), show);
        }
//        imwrite()
        imshow("Sharpen", show);
    }

    void DenoiseImage(Mat &image_cv) {
        //blur(image_cv, image_cv, Size(3,3), Point(-1,-1), BORDER_DEFAULT);
       GaussianBlur( image_cv, image_cv, Size(3,3), 0, 0, BORDER_DEFAULT );
        //medianBlur(image_cv, image_cv, 5);
    }

    std::string CopyFile(const std::string &kFileName) {
        if (kFileName.substr(kFileName.length() - 5) == ".jpeg") {
            std::string add_to_string = "Copy.jpeg";
            return kFileName.substr(0, kFileName.size() - 5) + add_to_string;
        } else if (kFileName.substr(kFileName.length() - 4) == ".jpg") {
            std::string add_to_string = "Copy.jpg";
            return kFileName.substr(0, kFileName.size() - 4) + add_to_string;
        } else {
            std::string add_to_string = "Copy.png";
            return kFileName.substr(0, kFileName.size() - 4) + add_to_string;
        }
    }

    void CompressImage(const std::string &kFileName, const double kCompression) {
        Mat image_cv = imread(kFileName, IMREAD_GRAYSCALE);
        Matrix<int, Dynamic, Dynamic> image_eigen;
        cv2eigen(image_cv, image_eigen);
        BDCSVD<MatrixXf> svd(image_eigen, ComputeThinU | Eigen::ComputeThinV);
        Matrix<double, Dynamic, Dynamic> sigma = svd.singularValues();
        Matrix<double, Dynamic, Dynamic> U = svd.matrixU();
        Matrix<double, Dynamic, Dynamic> Vt = svd.matrixV().transpose();
        unsigned int i = 0;
        unsigned int sum = 0;
        while (sigma[i] != 0) {
            sum += sigma[i];
            ++i;
        }

        //determines low rank
        unsigned int rank = 0;
        unsigned int temp_sum = 0;
        while (temp_sum <= kCompression * sum) {
            temp_sum += sigma[rank];
            ++rank;
        }
        Matrix<double, Dynamic, Dynamic> compressed_image = sigma[0] * U(all, 0) * Vt(0, all);
        for (int index = 1; index < rank; ++index) {
            compressed_image += sigma[index] * U(all, index) * Vt(index, all);
        }



    }

}  // namespace mylibrary
