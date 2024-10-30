
// RLTrainer.cpp
#include "RLTrainer.hpp"
#include <torch/torch.h>

RLTrainer::RLTrainer(const TrainingConfig& config)
    : config(config),
      policy_net(std::make_shared<DQN>(4, 128, 2)),
      target_net(std::make_shared<DQN>(4, 128, 2)),
      replay_buffer(config.replay_buffer_size),
      optimizer(policy_net->parameters()),
      epsilon(config.epsilon_start) {
    
    // Initialize target network with policy network's parameters
    target_net->copy_parameters(*policy_net);
    target_net->eval();  // Set to evaluation mode

    // Create parallel environments
    for (int i = 0; i < config.num_parallel_envs; i++) {
        envs.push_back(std::make_unique<PhysicsSystem>());
    }
}

std::vector<float> RLTrainer::getState(const PhysicsSystem& env) {
    const auto& bodies = env.getBodies();  // Using const version
    
    float cart_pos = bodies.cart->GetPosition().x;
    float cart_vel = bodies.cart->GetLinearVelocity().x;
    float pole_angle = bodies.pole->GetAngle();
    float pole_vel = bodies.pole->GetAngularVelocity();

    return {cart_pos, cart_vel, pole_angle, pole_vel};
}

float RLTrainer::getReward(const PhysicsSystem& env, bool done) {
    if (done) return -1.0f;
    return 1.0f;
}

bool RLTrainer::isDone(const PhysicsSystem& env) {
    const auto& bodies = env.getBodies();  // Using const version
    float pole_angle = bodies.pole->GetAngle();
    float cart_pos = bodies.cart->GetPosition().x;
    
    return std::abs(pole_angle) > 0.785398f || // 45 degrees
           std::abs(cart_pos) > 2.4f;
}

int RLTrainer::selectAction(const torch::Tensor& state) {
    if (torch::rand({1}).item<float>() > epsilon) {
        torch::NoGradGuard no_grad;
        auto action_values = policy_net->forward(state);
        return action_values.argmax(-1).item<int>();
    }
    return torch::randint(0, 2, {1}).item<int>();
}

void RLTrainer::optimizeModel() {
    if (replay_buffer.size() < config.batch_size) return;

    auto batch = replay_buffer.sample(config.batch_size);
    
    std::vector<torch::Tensor> state_batch;
    std::vector<int64_t> action_batch;
    std::vector<float> reward_batch;
    std::vector<torch::Tensor> next_state_batch;
    std::vector<float> done_batch;

    for (const auto& exp : batch) {
        state_batch.push_back(exp.state);
        action_batch.push_back(exp.action);
        reward_batch.push_back(exp.reward);
        next_state_batch.push_back(exp.next_state);
        done_batch.push_back(exp.done ? 0.0f : 1.0f);
    }

    auto states = torch::stack(state_batch);
    auto actions = torch::tensor(action_batch);
    auto rewards = torch::tensor(reward_batch);
    auto next_states = torch::stack(next_state_batch);
    auto dones = torch::tensor(done_batch);

    auto current_q_values = policy_net->forward(states).gather(1, actions.unsqueeze(1));
    
    auto next_q_values = target_net->forward(next_states);
    auto max_next_q_values = std::get<0>(next_q_values.max(1));  // Fixed tuple access
    auto expected_q_values = rewards + config.gamma * max_next_q_values * dones;

    auto loss = torch::mse_loss(current_q_values.squeeze(), expected_q_values);
    
    optimizer.zero_grad();
    loss.backward();
    optimizer.step();
}

void RLTrainer::updateTargetNetwork() {
    target_net->copy_parameters(*policy_net);  // Using new copy method
}