// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/model.h>
#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/photo/photo.hpp"
#include "randomizedSVD.h"

namespace mylibrary {
    void computeDiagonalSigma(Vector <double, Dynamic> &sigma, MatrixXd &diagonal_sigma);


    bool IsValidFile(const std::string &kFileName) {
        std::ifstream infile(kFileName);
        if (!infile.good()) {
            return false;
        }
        return !(kFileName.substr(kFileName.length() - 4) != "jpeg" && kFileName.substr(kFileName.length() - 3) != "jpg"
                 && kFileName.substr(kFileName.length() - 3) != "png");
    }

    void SharpenImage(const std::string &kFileName, const double cons, const bool rewrite_images, const bool new_file,
            const bool compress_image) {

        Mat image_cv = imread(kFileName, IMREAD_GRAYSCALE);

        Mat original = imread(kFileName, IMREAD_GRAYSCALE);

        DenoiseImage(image_cv);

        Mat laplacian;

        Laplacian(image_cv, laplacian, CV_16S, 1, 1, 0, BORDER_DEFAULT);

        Mat dst;

        convertScaleAbs(laplacian, dst);

        Mat show = original - cons*dst;

        if (compress_image) {
            CompressImage(show, .5);
        }

        if (rewrite_images) {
            imwrite(kFileName, show);
        } else if (new_file) {
            imwrite(CopyFile(kFileName), show);
        }

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

    void CompressImage(Mat &image_cv, const double kCompression) {


        if (kCompression == 1.0) {
            return;
        }

        MatrixXf image_eigen;
        cv2eigen(image_cv, image_eigen);


        //JacobiSVD<MatrixXf> svd;
        BDCSVD<MatrixXf> svd(image_eigen, Eigen::ComputeFullU | Eigen::ComputeFullV);
        //randomizedSVD::getSVD(image_eigen, svd);

        Eigen::Vector<double, Dynamic> sigma = svd.singularValues().cast<double>();
        MatrixXd diagonal_sigma(sigma.rows(), sigma.rows());
        computeDiagonalSigma(sigma, diagonal_sigma);

        std::cout << std::to_string(diagonal_sigma.rows()) + "x" + std::to_string(diagonal_sigma.cols()) << std::endl;
     //   std::cout << diagonal_sigma << std::endl;
        Matrix<double, Dynamic, Dynamic> U = svd.matrixU().cast<double>();
       // std::cout << std::to_string(U.rows()) + "x" + std::to_string(U.cols()) << std::endl;
        Matrix<double, Dynamic, Dynamic> Vt = svd.matrixV().transpose().cast<double>();
       // std::cout << std::to_string(Vt.rows()) + "x" + std::to_string(Vt.cols()) << std::endl;
        unsigned int i = 0;
        double sum = 0;
        while (i < sigma.size()) {
            sum += sigma[i];
            ++i;
        }

        std::cout << sum << std::endl;

        //determines low rank
        unsigned int rank = 0;
        double temp_sum = 0;

        while (temp_sum <= kCompression * sum) {
            temp_sum += sigma[rank];
            ++rank;
        }
        Matrix<double, Dynamic, Dynamic> compressed_image = sigma[0] * U(all, 0) * Vt(0, all);
        for (int index = 1; index < rank; ++index) {
            compressed_image += sigma[index] * U(all, index) * Vt(index, all);
        }
       //MatrixXd compressed_image = U * diagonal_sigma * Vt;
       std::cout << compressed_image << std::endl;
       Matrix<int, Dynamic, Dynamic> int_compressed = compressed_image.cast<int>();
       eigen2cv(int_compressed, image_cv);

       Mat final;

       convertScaleAbs(image_cv, final);
       std::cout << "HUH" << std::endl;
       std::cout << image_cv << std::endl;
       imshow("Compression", final);
    }
    void computeDiagonalSigma(Vector <double, Dynamic> &sigma, MatrixXd &diagonal_sigma) {
        diagonal_sigma.setZero();
        for (unsigned int i = 0; i < sigma.rows(); ++i) {
            diagonal_sigma(i,i) = sigma(i);
        }

    }

}  // namespace mylibrary
