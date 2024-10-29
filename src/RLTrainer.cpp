
// RLTrainer.cpp
#include "RLTrainer.hpp"

RLTrainer::RLTrainer(const TrainingConfig& config)
    : config(config),
      policy_net(std::make_shared<DQN>(4, 128, 2)),  // State size: 4, Action size: 2
      target_net(std::make_shared<DQN>(4, 128, 2)),
      replay_buffer(config.replay_buffer_size),
      optimizer(policy_net->parameters(), torch::optim::AdamOptions(0.001)),
      epsilon(config.epsilon_start) {
    
    // Initialize target network with policy network's weights
    target_net->load_state_dict(policy_net->state_dict());
    target_net->eval();

    // Create parallel environments
    for (int i = 0; i < config.num_parallel_envs; i++) {
        envs.push_back(std::make_unique<PhysicsSystem>());
    }
}

std::vector<float> RLTrainer::getState(const PhysicsSystem& env) {
    auto& bodies = env.getBodies();
    
    float cart_pos = bodies.cart->GetPosition().x;
    float cart_vel = bodies.cart->GetLinearVelocity().x;
    float pole_angle = bodies.pole->GetAngle();
    float pole_vel = bodies.pole->GetAngularVelocity();

    return {cart_pos, cart_vel, pole_angle, pole_vel};
}

float RLTrainer::getReward(const PhysicsSystem& env, bool done) {
    if (done) return -1.0f;
    return 1.0f;  // Reward for staying alive
}

bool RLTrainer::isDone(const PhysicsSystem& env) {
    auto& bodies = env.getBodies();
    float pole_angle = bodies.pole->GetAngle();
    float cart_pos = bodies.cart->GetPosition().x;
    
    return std::abs(pole_angle) > 0.785398f || // 45 degrees
           std::abs(cart_pos) > 2.4f;
}

int RLTrainer::selectAction(const torch::Tensor& state) {
    if (torch::rand({1}).item<float>() > epsilon) {
        torch::NoGradGuard no_grad;
        auto action_values = policy_net->forward(state);
        return action_values.argmax(1).item<int>();
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
    
    auto next_q_values = target_net->forward(next_states).max(1).values.detach();
    auto expected_q_values = rewards + config.gamma * next_q_values * dones;

    auto loss = torch::mse_loss(current_q_values.squeeze(), expected_q_values);
    
    optimizer.zero_grad();
    loss.backward();
    optimizer.step();
}

void RLTrainer::updateTargetNetwork() {
    target_net->load_state_dict(policy_net->state_dict());
}

void RLTrainer::train() {
    for (int episode = 0; episode < config.num_episodes; episode++) {
        // Reset all environments
        std::vector<torch::Tensor> states;
        for (auto& env : envs) {
            // Reset environment
            env = std::make_unique<PhysicsSystem>();
            auto state = getState(*env);
            states.push_back(torch::tensor(state));
        }

        float episode_reward = 0;
        
        for (int step = 0; step < config.max_steps; step++) {
            std::vector<int> actions;
            // Get actions for all environments
            for (const auto& state : states) {
                actions.push_back(selectAction(state));
            }

            // Step all environments
            std::vector<torch::Tensor> next_states;
            std::vector<float> rewards;
            std::vector<bool> dones;

            for (size_t i = 0; i < envs.size(); i++) {
                // Apply action
                float force = actions[i] == 0 ? -5.0f : 5.0f;
                envs[i]->applyForce(force);
                envs[i]->update();

                // Get new state and reward
                auto next_state = getState(*envs[i]);
                bool done = isDone(*envs[i]);
                float reward = getReward(*envs[i], done);

                // Store experience
                replay_buffer.push({
                    states[i],
                    actions[i],
                    reward,
                    torch::tensor(next_state),
                    done
                });

                next_states.push_back(torch::tensor(next_state));
                rewards.push_back(reward);
                dones.push_back(done);
                episode_reward += reward;
            }

            // Optimize model
            optimizeModel();

            // Move to next states
            states = next_states;

            // Check if all environments are done
            bool all_done = std::all_of(dones.begin(), dones.end(), [](bool d) { return d; });
            if (all_done) break;
        }

        // Update target network periodically
        if (episode % config.target_update == 0) {
            updateTargetNetwork();
        }

        // Decay epsilon
        epsilon = std::max(config.epsilon_end, 
                         epsilon * config.epsilon_decay);

        // Log progress
        if (episode % 10 == 0) {
            std::cout << "Episode: " << episode 
                      << " Average Reward: " << episode_reward / config.num_parallel_envs
                      << " Epsilon: " << epsilon << std::endl;
        }
    }
}