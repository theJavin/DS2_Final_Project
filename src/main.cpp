// main.cpp modifications
int main() {
    try {
        // Training configuration
        TrainingConfig config;
        config.num_episodes = 1000;
        config.num_parallel_envs = 16;
        
        // Create and run trainer
        RLTrainer trainer(config);
        trainer.train();
        
        // After training, run visualization with trained policy
        CartPoleSimulation sim;
        sim.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}