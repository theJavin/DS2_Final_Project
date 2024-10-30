
// Modified main.cpp
#include <iostream>
#include <exception>
#include "CartPoleSimulation.hpp"
#include "RLTrainer.hpp"
#include "TrainingConfig.hpp"

int main() {
    try {
        TrainingConfig config;
        config.num_episodes = 1000;
        config.num_parallel_envs = 16;
        
        RLTrainer trainer(config);
        trainer.train();
        
        CartPoleSimulation sim;
        sim.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}