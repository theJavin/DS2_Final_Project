// include/NeuralNetwork.hpp
#pragma once
#include <torch/torch.h>

class DQN : public torch::nn::Module {
public:
    DQN(int input_size, int hidden_size, int output_size) {
        fc1 = register_module("fc1", torch::nn::Linear(input_size, hidden_size));
        fc2 = register_module("fc2", torch::nn::Linear(hidden_size, hidden_size));
        fc3 = register_module("fc3", torch::nn::Linear(hidden_size, output_size));
    }

    torch::Tensor forward(torch::Tensor x) {
        x = torch::relu(fc1->forward(x));
        x = torch::relu(fc2->forward(x));
        return fc3->forward(x);
    }

    void copy_parameters(const DQN& other) {
        auto this_params = parameters();
        auto other_params = other.parameters();
        auto this_buffers = buffers();
        auto other_buffers = other.buffers();
        
        for (size_t i = 0; i < this_params.size(); i++) {
            this_params[i].data().copy_(other_params[i].data());
        }
        for (size_t i = 0; i < this_buffers.size(); i++) {
            this_buffers[i].copy_(other_buffers[i]);
        }
    }

private:
    torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr};
};