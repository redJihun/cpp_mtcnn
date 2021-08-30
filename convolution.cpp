#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>

#include <cstdio>

namespace Conv2D {
    cv::Mat_<float> forward(const cv::Mat_<float>& src, const cv::Mat_<float>& kernel, const int& stride, const int& padding){
        int k_center_x = kernel.cols / 2;
        int k_center_y = kernel.rows / 2;

        for(int i=0; i<src.rows; ++i){                      // rows
            for(int j=0; j<src.cols; ++j){                  // columns
                for(int m=0; m<kernel.rows; ++m){           // kernel rows
                    int mm = kernel.rows - 1 -m;            // row index of flipped kernel
                    for(int n=0; n<kernel.cols; ++n){       // kernel columns
                        int nn = kernel.cols - 1 - n;       // column index of flipped kernel

                        // index of input signal, used for checking boundary
                        int ii = i + (k_center_y - mm);
                        int jj = j + (k_center_x - nn);

                        // ignore input samples which are out of bound
                        if(ii>=0 && ii<src.rows && jj>=0 && jj<src.cols)
                            out[i][j] = in[ii][jj] * kernel[mm][nn];
                    }
                }
            }
        }

        printf(out)
    }

}

// double input[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

// cv::Mat_<float> spatialConvolution(const cv::Mat_<float> &src,
//                                    const cv::Mat_<float> &kernel) {
//   cv::Mat dst(src.rows, src.cols, src.type());

//   cv::Mat_<float> flipped_kernel;
//   cv::flip(kernel, flipped_kernel, -1);

//   const int dx = kernel.cols / 2;
//   const int dy = kernel.rows / 2;

//   for (int i = 0; i < src.rows; i++) {
//     for (int j = 0; j < src.cols; j++) {
//       float tmp = 0.0f;
//       for (int k = 0; k < flipped_kernel.rows; k++) {
//         for (int l = 0; l < flipped_kernel.cols; l++) {
//           int x = j - dx + l;
//           int y = i - dy + k;
//           if (x >= 0 && x < src.cols && y >= 0 && y < src.rows)
//             tmp += src.at<float>(y, x) * flipped_kernel.at<float>(k, l);
//         }
//       }
//       dst.at<float>(i, j) = saturate_cast<float>(tmp);
//     }
//   }
//   return dst.clone();
// }