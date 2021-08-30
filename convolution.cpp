#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>

double input[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

cv::Mat_<float> conv2D(){
    
}

cv::Mat_<float> spatialConvolution(const cv::Mat_<float> &src,
                                   const cv::Mat_<float> &kernel) {
  cv::Mat dst(src.rows, src.cols, src.type());

  cv::Mat_<float> flipped_kernel;
  cv::flip(kernel, flipped_kernel, -1);

  const int dx = kernel.cols / 2;
  const int dy = kernel.rows / 2;

  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.cols; j++) {
      float tmp = 0.0f;
      for (int k = 0; k < flipped_kernel.rows; k++) {
        for (int l = 0; l < flipped_kernel.cols; l++) {
          int x = j - dx + l;
          int y = i - dy + k;
          if (x >= 0 && x < src.cols && y >= 0 && y < src.rows)
            tmp += src.at<float>(y, x) * flipped_kernel.at<float>(k, l);
        }
      }
      dst.at<float>(i, j) = saturate_cast<float>(tmp);
    }
  }
  return dst.clone();
}