// test.cpp
#include <iostream>
#include <vector>
#include <cmath>

// 激活函数（Sigmoid）
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// 神经元
class Neuron {
public:
    Neuron(int numInputs) {
        weights.resize(numInputs);
        for (int i = 0; i < numInputs; i++) {
            weights[i] = static_cast<double>(rand()) / RAND_MAX; // 随机初始化权重
        }
    }

    double feedForward(const std::vector<double>& inputs) {
        double sum = 0.0;
        for (size_t i = 0; i < weights.size(); i++) {
            sum += weights[i] * inputs[i];
        }
        return sigmoid(sum);
    }

private:
    std::vector<double> weights;
};

// 简单的神经网络
class NeuralNetwork {
public:
    NeuralNetwork(int numInputs, int numHidden, int numOutputs) {
        // 创建隐藏层神经元
        for (int i = 0; i < numHidden; i++) {
            hiddenLayer.push_back(Neuron(numInputs));
        }
        // 创建输出层神经元
        for (int i = 0; i < numOutputs; i++) {
            outputLayer.push_back(Neuron(numHidden));
        }
    }

    std::vector<double> feedForward(const std::vector<double>& inputs) {
        // 计算隐藏层输出
        std::vector<double> hiddenOutputs;
        for (auto& neuron : hiddenLayer) {
            hiddenOutputs.push_back(neuron.feedForward(inputs));
        }

        // 计算输出层输出
        std::vector<double> outputs;
        for (auto& neuron : outputLayer) {
            outputs.push_back(neuron.feedForward(hiddenOutputs));
        }

        return outputs;
    }

private:
    std::vector<Neuron> hiddenLayer;
    std::vector<Neuron> outputLayer;
};

int main() {
    NeuralNetwork nn(3, 4, 2); // 输入3个特征，隐藏层4个神经元，输出2个类别

    // 示例输入
    std::vector<double> input = {1.0, 0.5, -1.5};
    
    // 前向传播
    std::vector<double> output = nn.feedForward(input);

    // 输出结果
    std::cout << "Output: ";
    for (const auto& val : output) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}