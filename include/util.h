//
// Created by Sarish Deotale on 5/6/20.
//

#ifndef FINALPROJECT_UTIL_H
#define FINALPROJECT_UTIL_H

#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET

#include <vector>
#include "Eigen/Sparse"
#include "Eigen/Dense"
#include "Eigen/Eigenvalues"

namespace REDSVD {

    typedef Eigen::SparseMatrix<float, Eigen::RowMajor> SMatrixXf;
    typedef std::vector<std::pair<int, float> > fv_t;

    class Util{
    public:
        static void convertFV2Mat(const std::vector<fv_t>& fvs, SMatrixXf& A);
        static void sampleGaussianMat(Eigen::MatrixXf& x);
        static void processGramSchmidt(Eigen::MatrixXf& mat);
        static double getSec();

    private:
        static void sampleTwoGaussian(float& f1, float& f2);
    };

}

#endif //FINALPROJECT_UTIL_H
