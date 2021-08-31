#include <iostream>
#include <vector>

#include "Convolution2D.h"

namespace Convolution2D {
int getOutputRes(const int width_in, const int width_filter, const int stride,
                 const int padding) {
  return (width_in - width_filter + 2 * padding) / stride + 1;
}

std::vector<std::vector<float>>
forward(const std::vector<std::vector<float>> src,
        const std::vector<std::vector<float>> kernel, int stride,
        int padding) {
  int src_rows = src.size() / src[0].size();
  int src_cols = src[0].size() / sizeof(float);
  int kernel_rows = kernel.size() / kernel[0].size();
  int kernel_cols = kernel[0].size() / sizeof(float);
  int h_out_res = getOutputRes(src_rows, kernel_rows, stride, padding);
  int w_out_res = getOutputRes(src_cols, kernel_cols, stride, padding);

  std::vector<std::vector<float>> output_image(
      h_out_res, std::vector<float>(w_out_res, 0));

  for (int i_src = -padding, i_out = 0;
       i_src < src_rows + padding - h_out_res + 1;
       i_src += stride, i_out++) { // rows

    for (int j_src = -padding, j_out = 0;
         j_src < src_cols + padding - w_out_res + 1;
         j_src += stride, j_out++) { // columns
      float sum = 0;

      for (int i_kernel = 0, i_in = i_src; i_kernel < h_out_res;
           i_kernel++, i_in++) { // kernel rows

        for (int j_kernel = 0, j_in = j_src; j_kernel < w_out_res;
             j_kernel++, j_in++) { // kernel columns

          // ignore input samples which are out of bound
          if (i_in >= 0 && i_in < src_rows && j_in >= 0 && j_in < src_cols)
            sum += src[i_in][j_in] * kernel[i_kernel][j_kernel];
        }
      }
      // 세그멘테이션 오류 발생
      output_image[i_out][j_out] = sum;
      // std::cout << sum << std::endl;
    }
  }
  std::cout << output_image.size() << std::endl;
  std::cout << output_image[0].size() << std::endl;

  for (int i = 0; i < output_image.size(); i++) {
    for (int j = 0; j < output_image[i].size(); j++) {
      std::cout << output_image[i][j];
    }
    std::cout << std::endl;
  }

  return output_image;
}

// void backward(const std::vector<std::vector<float>> filter,
//               const std::vector<std::vector<float>> output_grad,
//               std::vector<std::vector<float>> input_grad) {
//   int input_grad_height = input_grad.size() / input_grad[0].size();
//   int input_grad_width = input_grad[0].size() / sizeof(float);

    
  
//   for (int i = 0; i < input_grad_width * input_grad_height; i++)
//     input_grad.values_[i] = 0.0;

//   for (int j_in_base = -filter.j_padding_, j_out = 0;
//        j_in_base < input_grad.height_ + filter.j_padding_ - filter.j_res_ + 1;
//        j_in_base += filter.j_stride_, j_out++)
//     for (int i_in_base = -filter.i_padding_, i_out = 0;
//          i_in_base < input_grad.width_ + filter.i_padding_ - filter.i_res_ + 1;
//          i_in_base += filter.i_stride_, i_out++) {
//       for (int j_f = 0, j_in = j_in_base; j_f < filter.j_res_; j_f++, j_in++)
//         for (int i_f = 0, i_in = i_in_base; i_f < filter.i_res_;
//              i_f++, i_in++) {
//           if (input_grad.isValid(i_in, j_in) == true)
//             input_grad.getValue(i_in, j_in) +=
//                 filter.getWeight(i_f, j_f) * output_grad.getValue(i_out, j_out);
//           // else // zero padding
//         }
//     }
// }

} // namespace Convolution2D

int main(int argc, const char **argv) {

  std::vector<std::vector<float>> input(5, std::vector<float>(5, 1));
  std::vector<std::vector<float>> kernel = {{1, 1, 1}, {0, 0, 0}, {-2, -2, -2}};

  Conv2D::forward(input, kernel, 1, 0);
}