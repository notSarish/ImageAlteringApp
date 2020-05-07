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

    void SharpenImage(const std::string &kFileName, const double cons, const bool rewrite_images, const bool new_file) {

        Mat image_cv = imread(kFileName, IMREAD_GRAYSCALE);

        Mat original = imread(kFileName, IMREAD_GRAYSCALE);

        DenoiseImage(image_cv);

        Mat laplacian;

        Laplacian(image_cv, laplacian, CV_16S, 1, 1, 0, BORDER_DEFAULT);

        Mat dst;

        convertScaleAbs(laplacian, dst);

        Mat show = original - cons*dst;



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

    bool CompressImage(const std::string &kFileName, const double kCompression, const bool kRewriteImage, const bool kMakeNewFile) {

        Mat image_cv = imread(kFileName, IMREAD_GRAYSCALE);
        if (kCompression == 1.0) {
            imshow("Compression", image_cv);
            return true;
        } else if (kCompression < 0 || kCompression > 1) {
            return false;
        }


        MatrixXf image_eigen;
        cv2eigen(image_cv, image_eigen);

        //take svd of matrix
        BDCSVD<MatrixXf> svd(image_eigen, Eigen::ComputeFullU | Eigen::ComputeFullV);

        //separating svd into its components
        Eigen::Vector<double, Dynamic> sigma = svd.singularValues().cast<double>();

        MatrixXd diagonal_sigma(sigma.rows(), sigma.rows());

        //this function essentially creates a diagonal matrix from the singular values
        computeDiagonalSigma(sigma, diagonal_sigma);

        Matrix<double, Dynamic, Dynamic> U = svd.matrixU().cast<double>();
        Matrix<double, Dynamic, Dynamic> Vt = svd.matrixV().transpose().cast<double>();

        //sums all the singular values
        unsigned int i = 0;
        double sum = 0;
        while (i < sigma.size()) {
            sum += sigma[i];
            ++i;
        }


        //determines low rank by finding which singular values still results in temp_sum < kCompression * sum
        unsigned int rank = 0;
        double temp_sum = 0;

        while (temp_sum <= kCompression * sum) {
            temp_sum += sigma[rank];
            ++rank;
        }

        //creates low rank approximation by multiplying sigma[i] * the ith column of U * ith row of Vt
        Matrix<double, Dynamic, Dynamic> compressed_image = sigma[0] * U(all, 0) * Vt(0, all);
        for (int index = 1; index < rank; ++index) {
            compressed_image += sigma[index] * U(all, index) * Vt(index, all);
        }


        //essentially converts matrix to something opencv can convert to an image
       Matrix<int, Dynamic, Dynamic> int_compressed = compressed_image.cast<int>();
       eigen2cv(int_compressed, image_cv);
       Mat final;
       convertScaleAbs(image_cv, final);

        if (kRewriteImage) {
            imwrite(kFileName, final);
        } else if (kMakeNewFile) {
            imwrite(CopyFile(kFileName), final);
        }

       imshow("Compression", final);
       return true;
    }
    void computeDiagonalSigma(Vector <double, Dynamic> &sigma, MatrixXd &diagonal_sigma) {
        diagonal_sigma.setZero();
        for (unsigned int i = 0; i < sigma.rows(); ++i) {
            diagonal_sigma(i,i) = sigma(i);
        }

    }


}  // namespace mylibrary
