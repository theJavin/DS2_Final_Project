// include/ReplayBuffer.hpp
#pragma once
#include <deque>
#include <vector>
#include <random>
#include <torch/torch.h>

struct Experience {
    torch::Tensor state;
    int action;
    float reward;
    torch::Tensor next_state;
    bool done;
};

class ReplayBuffer {
public:
    ReplayBuffer(size_t capacity) : capacity(capacity) {}

    void push(const Experience& exp) {
        if (buffer.size() >= capacity) {
            buffer.pop_front();
        }
        buffer.push_back(exp);
    }

    std::vector<Experience> sample(size_t batch_size) {
        std::vector<Experience> batch;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, buffer.size() - 1);

        for (size_t i = 0; i < batch_size && i < buffer.size(); i++) {
            batch.push_back(buffer[dis(gen)]);
        }
        return batch;
    }

    size_t size() const { return buffer.size(); }

private:
    std::deque<Experience> buffer;
    size_t capacity;
};