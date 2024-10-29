
// RLTrainer.hpp
#pragma once
#include <memory>
#include <vector>
#include "PhysicsSystem.hpp"
#include "NeuralNetwork.hpp"
#include "ReplayBuffer.hpp"

struct TrainingConfig {
    int num_episodes = 1000;
    int max_steps = 500;
    float gamma = 0.99f;
    float epsilon_start = 1.0f;
    float epsilon_end = 0.01f;
    float epsilon_decay = 0.995f;
    int batch_size = 64;
    int target_update = 10;
    size_t replay_buffer_size = 10000;
    int num_parallel_envs = 16;
};

class RLTrainer {
public:
    RLTrainer(const TrainingConfig& config);
    void train();
    
    std::vector<float> getState(const PhysicsSystem& env);
    float getReward(const PhysicsSystem& env, bool done);
    bool isDone(const PhysicsSystem& env);

private:
    TrainingConfig config;
    std::shared_ptr<DQN> policy_net;
    std::shared_ptr<DQN> target_net;
    ReplayBuffer replay_buffer;
    torch::optim::Adam optimizer;
    std::vector<std::unique_ptr<PhysicsSystem>> envs;
    float epsilon;

    int selectAction(const torch::Tensor& state);
    void optimizeModel();
    void updateTargetNetwork();
};