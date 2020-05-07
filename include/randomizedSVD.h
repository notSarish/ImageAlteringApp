//
// Created by Sarish Deotale on 5/6/20.
//

#ifndef FINALPROJECT_RANDOMIZEDSVD_H
#define FINALPROJECT_RANDOMIZEDSVD_H

#include <iostream>
#include "Eigen/Core"
#include "Eigen/QR"
#include "util.h"


namespace randomizedSVD {
   using namespace REDSVD;
   using namespace Eigen;



   template<class Mat>
   void getSVD(Mat &image_eigen, Eigen::JacobiSVD<MatrixXf> &svd) {
       int r = (image_eigen.rows() < image_eigen.cols()) ? image_eigen.rows() : image_eigen.cols();

       Eigen::MatrixXf O(image_eigen.rows(), r);
       // Util::sampleGaussianMat(O);
       Util::sampleGaussianMat(O);

       Eigen::MatrixXf Y = image_eigen.transpose() * O.matrix();
       //std::cout << Y;
       Util::processGramSchmidt(Y);
       Eigen::MatrixXf B = image_eigen * Y;

       Eigen::MatrixXf P(B.cols(), r);
       Util::sampleGaussianMat(P);
       Eigen::MatrixXf Z = B * P;

       // Orthonormalize Z
       Util::processGramSchmidt(Z);

       // Range(C) = Range(B)
       Eigen::MatrixXf C = Z.transpose() * B;

       Eigen::JacobiSVD<Eigen::MatrixXf> svdOfC(C, Eigen::ComputeThinU | Eigen::ComputeThinV);
       svd = svdOfC;

   }


}

#endif //FINALPROJECT_RANDOMIZEDSVD_H
