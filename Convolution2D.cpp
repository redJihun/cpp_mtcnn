#include <algorithm>
#include <cstdio>
#include <vector>

#include "Convolution2D.h"

namespace Convolution2D {
int getOutputRes(const int &width_in, const int &width_filter,
                 const int &stride, const int &padding) {
  return (width_in - width_filter + 2 * padding) / stride + 1;
}

float forward(const std::vector<std::vector<float>> &src,
              const std::vector<std::vector<float>> &kernel, const int &stride,
              const int &padding) {
  int s_rows = src.size() / src[0].size();
  int s_cols = src[0].size() / sizeof(float);
  int k_rows = kernel.size() / kernel[0].size();
  int k_cols = kernel[0].size() / sizeof(float);
  int h_out_res = getOutputRes(s_rows, k_rows, stride, padding);
  int w_out_res = getOutputRes(s_cols, k_cols, stride, padding);

  std::vector<std::vector<float>> output_image(h_out_res, std::vector<float> (w_out_res, 0));

  for (int i_src = -padding, i_out = 0;
       i_src < s_rows + padding - h_out_res + 1;
       i_src += stride, i_out++) { // rows

    for (int j_src = -padding, j_out = 0;
         j_src < s_cols + padding - w_out_res + 1;
         j_src += stride, j_out++) { // columns
      T sum = (T)0;

      for (int i_kernel = 0, i_in = i_src; i_kernel < h_out_res;
           i_kernel++, i_in++) { // kernel rows

        for (int j_kernel = 0, j_in = j_src; j_kernel < w_out_res;
             j_kernel++, j_in++) { // kernel columns

          // ignore input samples which are out of bound
          if (i_in >= 0 && i_in < s_rows && j_in >= 0 && j_in < s_cols)
            sum += src[i_in][j_in] * kernel[i_kernel][j_kernel];
        }

        output_image[i_out][j_out] = sum;
      }
    }
  }

  std::printf(output_image.);
}

} // namespace Convolution2D

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
