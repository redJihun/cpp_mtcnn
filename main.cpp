#include "Convolution2D.h"
#include <vector>
#include <iostream>

int main() {
  std::vector<std::vector<float>> input(5, std::vector<float>(5, 1));
  std::vector<std::vector<float>> kernel = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}};

  std::vector<std::vector<float>> output = Conv2D::forward(kernel, input, 1, 0);
}