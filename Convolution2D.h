#include <vector>

typedef float T;

namespace Convolution2D
{
	int getOutputRes(const int& width_in, const int& width_filter, const int& stride, const int& padding);

	// input_image = prev_laver, output_image = next_layer
	void forward(const std::vector<std::vector<float>>& filter, const std::vector<std::vector<float>>& input_image, const int& stride, const int& padding);

	// input_grad = gradient of prev layer, output_grad = gradient of next layer
	void backward(const std::vector<std::vector<float>>& filter, const std::vector<std::vector<float>>& output_grad, std::vector<std::vector<float>>& input_grad);

	void updateWeights(const T& eta_, const T& alpha_, const std::vector<std::vector<float>>& output_grad, const std::vector<std::vector<float>>& input_act, std::vector<std::vector<float>>& filter);
};

namespace Conv2D = Convolution2D;
