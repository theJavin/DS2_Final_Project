
// include/RLTrainer.hpp
#pragma once
#include <memory>
#include <vector>
#include "PhysicsSystem.hpp"
#include "NeuralNetwork.hpp"
#include "ReplayBuffer.hpp"
#include "TrainingConfig.hpp"
#include <torch/torch.h>

class RLTrainer {
public:
    RLTrainer(const TrainingConfig& config);
    void train();
    
private:
    TrainingConfig config;
    std::shared_ptr<DQN> policy_net;
    std::shared_ptr<DQN> target_net;
    ReplayBuffer replay_buffer;
    torch::optim::Adam optimizer;
    std::vector<std::unique_ptr<PhysicsSystem>> envs;
    float epsilon;

    std::vector<float> getState(const PhysicsSystem& env);
    float getReward(const PhysicsSystem& env, bool done);
    bool isDone(const PhysicsSystem& env);
    int selectAction(const torch::Tensor& state);
    void optimizeModel();
    void updateTargetNetwork();
};