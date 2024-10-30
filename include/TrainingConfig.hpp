// include/TrainingConfig.hpp
#pragma once

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