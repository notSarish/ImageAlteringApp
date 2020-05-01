////
//// Created by Sarish Deotale on 4/29/20.
////
//
//#include "mylibrary/compression.h"
//#include <mylibrary/model.h>
//#include <Eigen/Dense>
//#include <fstream>
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/core/eigen.hpp"
//#include "opencv2/photo/photo.hpp"
//
//
//namespace mylibrary {
//    using namespace cv;
//    using namespace Eigen;
//    void Compress_Image(const std::string &kFileName, const double percent_of_image) {
//        Mat image_cv = imread(kFileName, IMREAD_GRAYSCALE);
//        Matrix<int, Dynamic, Dynamic> image_eigen;
//        cv2eigen(image_cv, image_eigen);
//       // BDCSVD<MatrixXd> svd(image_eigen, ComputeFullV| ComputeFullU);
//
//        //BDCSVD(&image_eigen);
//
//    }
//}