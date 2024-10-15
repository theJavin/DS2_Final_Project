#include <mujoco/mujoco.h>
#include <vector>
#include <random>
#include <cmath>
#include <iostream>

class CartPoleEnv {
public:
    struct State {
        double cart_position;
        double cart_velocity;
        double pole_angle;
        double pole_angular_velocity;
    };

    CartPoleEnv() {
        char error[1000] = "Could not load model";
        m = mj_loadXML("cartpole.xml", 0, error, 1000);
        if (!m) {
            mju_error_s("Load model error: %s", error);
            return;
        }

        d = mj_makeData(m);
        reset();
    }

    ~CartPoleEnv() {
        mj_deleteData(d);
        mj_deleteModel(m);
    }

    State reset() {
        mj_resetData(m, d);
        mju_copy(d->qpos, m->qpos0, m->nq);
        mju_copy(d->qvel, m->qvel0, m->nv);
        mj_forward(m, d);
        return get_state();
    }

    std::pair<State, double> step(int action) {
        // Apply force based on action
        d->ctrl[0] = (action == 0) ? -10.0 : 10.0;

        // Step the simulation
        mj_step(m, d);

        State new_state = get_state();
        double reward = 1.0;  // You might want to implement a more sophisticated reward function

        // Check if episode is done (e.g., pole angle too large)
        bool done = std::abs(new_state.pole_angle) > 0.261799;  // about 15 degrees

        return {new_state, done ? 0.0 : reward};
    }

private:
    mjModel* m;
    mjData* d;

    State get_state() {
        return {
            d->qpos[0],  // cart position
            d->qvel[0],  // cart velocity
            d->qpos[1],  // pole angle
            d->qvel[1]   // pole angular velocity
        };
    }
};

class Agent {
public:
    Agent(int state_size, int action_size) : state_size(state_size), action_size(action_size) {
        // Initialize Q-table
        q_table.resize(100, std::vector<double>(action_size, 0.0));
    }

    int get_action(const CartPoleEnv::State& state) {
        // Implement epsilon-greedy action selection
        if (((double) rand() / (RAND_MAX)) < epsilon) {
            return rand() % action_size;
        } else {
            int state_index = discretize_state(state);
            return std::max_element(q_table[state_index].begin(), q_table[state_index].end()) - q_table[state_index].begin();
        }
    }

    void update(const CartPoleEnv::State& state, int action, double reward, const CartPoleEnv::State& next_state) {
        int state_index = discretize_state(state);
        int next_state_index = discretize_state(next_state);

        double max_next_q = *std::max_element(q_table[next_state_index].begin(), q_table[next_state_index].end());
        q_table[state_index][action] += learning_rate * (reward + discount_factor * max_next_q - q_table[state_index][action]);
    }

private:
    int state_size;
    int action_size;
    std::vector<std::vector<double>> q_table;
    double epsilon = 0.1;
    double learning_rate = 0.1;
    double discount_factor = 0.99;

    int discretize_state(const CartPoleEnv::State& state) {
        // Simple discretization, you might want to implement a more sophisticated method
        int x = std::min(std::max((int)((state.cart_position + 2.4) / 4.8 * 10), 0), 9);
        int x_dot = std::min(std::max((int)((state.cart_velocity + 10) / 20 * 10), 0), 9);
        int theta = std::min(std::max((int)((state.pole_angle + 0.261799) / 0.523598 * 10), 0), 9);
        int theta_dot = std::min(std::max((int)((state.pole_angular_velocity + 10) / 20 * 10), 0), 9);
        return x + 10 * x_dot + 100 * theta + 1000 * theta_dot;
    }
};

int main() {
    CartPoleEnv env;
    Agent agent(4, 2);  // 4 state variables, 2 possible actions

    for (int episode = 0; episode < 1000; ++episode) {
        auto state = env.reset();
        double total_reward = 0;
        int step = 0;

        while (step < 200) {  // Max 200 steps per episode
            int action = agent.get_action(state);
            auto [next_state, reward] = env.step(action);
            
            agent.update(state, action, reward, next_state);
            
            total_reward += reward;
            state = next_state;

            if (reward == 0) {  // Episode ended early
                break;
            }
            step++;
        }

        std::cout << "Episode " << episode << ": Total reward: " << total_reward << ", Steps: " << step << std::endl;
    }

    return 0;
}