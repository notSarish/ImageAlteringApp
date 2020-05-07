//
// Created by Sarish Deotale on 5/6/20.
//
#include <iostream>
#include "randomizedSVD.h"
#include "Eigen/Core"
#include "Eigen/QR"
#include "util.h"

namespace randomizedSVD {

    using namespace Eigen;
    using namespace REDSVD;

//    template<class Mat>
//    void getSVD(Mat &image_eigen) {
//        int r = (image_eigen.rows() < image_eigen.cols()) ? image_eigen.rows() : image_eigen.cols();
//
//        MatrixXf O(image_eigen.rows(), r);
//       // Util::sampleGaussianMat(O);
//        Util::sampleGaussianMat(O);
//
//        MatrixXf Y = image_eigen.transpose() * O;
//
//        auto QR = Y.fullPivHouseholderQr();
//        Eigen::MatrixXd Q = QR.matrixQ();
//        std::cout << Q;
//        //Eigen::MatrixXd R = QR.matrixQR().triangularView<Upper>();
//    }



}