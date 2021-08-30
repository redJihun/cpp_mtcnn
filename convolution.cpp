#include <vector>
#include <cstdio>

namespace Conv2D {
    float forward(const std::vector<std::vector<float>>& src, const std::vector<std::vector<float>>& kernel, const int& stride, const int& padding){
        int s_rows = src.size() / src[0].size();
        int s_cols = src[0].size() / sizeof(float);
        int k_rows = kernel.size() / kernel[0].size();
        int k_cols = kernel[0].size() / sizeof(float);

        int k_center_y = k_rows / 2;
        int k_center_x = k_cols / 2;

        for(int i=0; i<s_rows; ++i){                      // rows

            for(int j=0; j<s_cols; ++j){                  // columns
                T sum = (T)0;

                for(int m=0; m<k_rows; ++m){           // kernel rows
                    int mm = k_rows - 1 -m;            // row index of flipped kernel

                    for(int n=0; n<k_cols; ++n){       // kernel columns
                        int nn = k_cols - 1 - n;       // column index of flipped kernel

                        // index of input signal, used for checking boundary
                        int ii = i + (k_center_y - mm);
                        int jj = j + (k_center_x - nn);

                        // ignore input samples which are out of bound
                        if(ii>=0 && ii<s_rows && jj>=0 && jj<s_cols)
                            out[i][j] = in[ii][jj] * kernel[mm][nn];
                    }
                }
            }
        }

        printf(out);
    }

}

// double input[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

// <float> spatialConvolution(const <float> &src,
//                                    const <float> &kernel) {
//   cv::Mat dst(src.rows, src.cols, src.type());

//   <float> flipped_kernel;
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