#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>

const float SCALE = 30.0f; // Box2D works in meters, SFML in pixels. This is our conversion factor.

class PhysicsEngine {
private:
    b2World world;
    b2Body* cartBody;
    b2Body* poleBody;
    b2RevoluteJoint* joint;

public:
    PhysicsEngine() : world(b2Vec2(0.0f, 9.8f)) {
        // Create cart
        b2BodyDef cartBodyDef;
        cartBodyDef.type = b2_dynamicBody;
        cartBodyDef.position.Set(0.0f, 10.0f);
        cartBody = world.CreateBody(&cartBodyDef);

        b2PolygonShape cartShape;
        cartShape.SetAsBox(1.0f, 0.5f);

        b2FixtureDef cartFixtureDef;
        cartFixtureDef.shape = &cartShape;
        cartFixtureDef.density = 1.0f;
        cartBody->CreateFixture(&cartFixtureDef);

        // Create pole
        b2BodyDef poleBodyDef;
        poleBodyDef.type = b2_dynamicBody;
        poleBodyDef.position.Set(0.0f, 8.5f);
        poleBody = world.CreateBody(&poleBodyDef);

        b2PolygonShape poleShape;
        poleShape.SetAsBox(0.1f, 1.5f);

        b2FixtureDef poleFixtureDef;
        poleFixtureDef.shape = &poleShape;
        poleFixtureDef.density = 1.0f;
        poleBody->CreateFixture(&poleFixtureDef);

        // Create joint
        b2RevoluteJointDef jointDef;
        jointDef.bodyA = cartBody;
        jointDef.bodyB = poleBody;
        jointDef.localAnchorA.Set(0.0f, 0.0f);
        jointDef.localAnchorB.Set(0.0f, 1.5f);
        jointDef.enableLimit = false;
        joint = (b2RevoluteJoint*)world.CreateJoint(&jointDef);
    }

    void step(float timeStep, int velocityIterations, int positionIterations) {
        world.Step(timeStep, velocityIterations, positionIterations);
    }

    void applyForce(float force) {
        cartBody->ApplyForceToCenter(b2Vec2(force, 0), true);
    }

    b2Vec2 getCartPosition() const {
        return cartBody->GetPosition();
    }

    float getPoleAngle() const {
        return poleBody->GetAngle();
    }

    void reset() {
        cartBody->SetTransform(b2Vec2(0.0f, 10.0f), 0.0f);
        poleBody->SetTransform(b2Vec2(0.0f, 8.5f), 0.0f);
        cartBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
        poleBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
        cartBody->SetAngularVelocity(0.0f);
        poleBody->SetAngularVelocity(0.0f);
    }
};

class CartPole {
private:
    PhysicsEngine physicsEngine;
    const float force_mag = 500.0f;
    const float x_boundary = 8.0f;
    const float theta_boundary = M_PI / 6;

public:
    CartPole() {}

    void reset() {
        physicsEngine.reset();
    }

    bool step(int action) {
        float force = action == 1 ? force_mag : -force_mag;
        physicsEngine.applyForce(force);
        physicsEngine.step(1.0f/60.0f, 6, 2);

        b2Vec2 position = physicsEngine.getCartPosition();
        float angle = physicsEngine.getPoleAngle();

        return std::abs(position.x) < x_boundary && std::abs(angle) < theta_boundary;
    }

    float getX() const { return physicsEngine.getCartPosition().x; }
    float getTheta() const { return physicsEngine.getPoleAngle(); }
    float getXBoundary() const { return x_boundary; }
    float getThetaBoundary() const { return theta_boundary; }
};

class Visualizer {
private:
    sf::RenderWindow window;
    const float cart_width = 60.0f;
    const float cart_height = 30.0f;
    const float pole_length = 90.0f;
    const float pole_thickness = 6.0f;

public:
    Visualizer() : window(sf::VideoMode(800, 400), "Cart Pole Simulation") {
        window.setFramerateLimit(60);
    }

    void render(const CartPole& cart_pole) {
        window.clear(sf::Color::White);

        // Draw boundaries
        sf::RectangleShape leftBoundary(sf::Vector2f(5, 400));
        leftBoundary.setFillColor(sf::Color::Red);
        leftBoundary.setPosition(400 - cart_pole.getXBoundary() * SCALE, 0);
        window.draw(leftBoundary);

        sf::RectangleShape rightBoundary(sf::Vector2f(5, 400));
        rightBoundary.setFillColor(sf::Color::Red);
        rightBoundary.setPosition(400 + cart_pole.getXBoundary() * SCALE, 0);
        window.draw(rightBoundary);

        // Calculate cart position
        float cart_center_x = 400 + cart_pole.getX() * SCALE;

        // Draw cart
        sf::RectangleShape cart(sf::Vector2f(cart_width, cart_height));
        cart.setFillColor(sf::Color::Blue);
        cart.setPosition(cart_center_x - cart_width / 2, 300 - cart_height / 2);
        window.draw(cart);

        // Draw pole
        sf::RectangleShape pole(sf::Vector2f(pole_thickness, pole_length));
        pole.setFillColor(sf::Color::Green);
        pole.setOrigin(pole_thickness / 2, pole_length);
        pole.setPosition(cart_center_x, 300);
        pole.setRotation(-cart_pole.getTheta() * 180 / M_PI);
        window.draw(pole);

        window.display();
    }

    bool isOpen() const { return window.isOpen(); }

    int handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A)
                    return 0;  // Move left
                if (event.key.code == sf::Keyboard::D)
                    return 1;  // Move right
                if (event.key.code == sf::Keyboard::M)
                    return 2;  // Switch mode
            }
        }
        return -1;  // No relevant input
    }
};

class QLearning {
private:
    std::vector<std::vector<std::vector<std::vector<std::vector<double>>>>> q_table;
    const int num_x_bins = 10;
    const int num_theta_bins = 10;
    const int num_x_dot_bins = 10;
    const int num_theta_dot_bins = 10;
    const int num_actions = 2;
    const double learning_rate = 0.1;
    const double discount_factor = 0.99;
    const double epsilon = 0.1;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

public:
    QLearning() : gen(std::random_device()()), dis(0.0, 1.0) {
        q_table.resize(num_x_bins, 
            std::vector<std::vector<std::vector<std::vector<double>>>>(num_theta_bins,
                std::vector<std::vector<std::vector<double>>>(num_x_dot_bins,
                    std::vector<std::vector<double>>(num_theta_dot_bins,
                        std::vector<double>(num_actions, 0.0)))));
    }

    int get_state_index(double value, double min_value, double max_value, int num_bins) {
        int index = static_cast<int>((value - min_value) / (max_value - min_value) * num_bins);
        return std::max(0, std::min(num_bins - 1, index));
    }

    int choose_action(const CartPole& cart_pole) {
        if (dis(gen) < epsilon) {
            return dis(gen) < 0.5 ? 0 : 1;  // Explore: random action
        }
        
        int x_index = get_state_index(cart_pole.getX(), -cart_pole.getXBoundary(), cart_pole.getXBoundary(), num_x_bins);
        int theta_index = get_state_index(cart_pole.getTheta(), -cart_pole.getThetaBoundary(), cart_pole.getThetaBoundary(), num_theta_bins);
        int x_dot_index = get_state_index(0, -10, 10, num_x_dot_bins); // Placeholder, as we don't have x_dot
        int theta_dot_index = get_state_index(0, -10, 10, num_theta_dot_bins); // Placeholder, as we don't have theta_dot

        // Exploit: choose best action
        return q_table[x_index][theta_index][x_dot_index][theta_dot_index][0] > 
               q_table[x_index][theta_index][x_dot_index][theta_dot_index][1] ? 0 : 1;
    }

    void update_q_table(const CartPole& old_state, int action, double reward, const CartPole& new_state) {
        int old_x_index = get_state_index(old_state.getX(), -old_state.getXBoundary(), old_state.getXBoundary(), num_x_bins);
        int old_theta_index = get_state_index(old_state.getTheta(), -old_state.getThetaBoundary(), old_state.getThetaBoundary(), num_theta_bins);
        int old_x_dot_index = get_state_index(0, -10, 10, num_x_dot_bins); // Placeholder
        int old_theta_dot_index = get_state_index(0, -10, 10, num_theta_dot_bins); // Placeholder

        int new_x_index = get_state_index(new_state.getX(), -new_state.getXBoundary(), new_state.getXBoundary(), num_x_bins);
        int new_theta_index = get_state_index(new_state.getTheta(), -new_state.getThetaBoundary(), new_state.getThetaBoundary(), num_theta_bins);
        int new_x_dot_index = get_state_index(0, -10, 10, num_x_dot_bins); // Placeholder
        int new_theta_dot_index = get_state_index(0, -10, 10, num_theta_dot_bins); // Placeholder

        double old_q_value = q_table[old_x_index][old_theta_index][old_x_dot_index][old_theta_dot_index][action];
        double max_new_q_value = std::max(q_table[new_x_index][new_theta_index][new_x_dot_index][new_theta_dot_index][0],
                                          q_table[new_x_index][new_theta_index][new_x_dot_index][new_theta_dot_index][1]);

        q_table[old_x_index][old_theta_index][old_x_dot_index][old_theta_dot_index][action] = 
            old_q_value + learning_rate * (reward + discount_factor * max_new_q_value - old_q_value);
    }
};

int main() {
    CartPole cart_pole;
    Visualizer visualizer;
    QLearning q_learning;

    const int num_episodes = 1000;
    std::vector<int> episode_lengths;
    bool manual_mode = false;

    for (int episode = 0; episode < num_episodes; ++episode) {
        cart_pole.reset();
        bool done = false;
        int step = 0;

        while (!done && step < 1000 && visualizer.isOpen()) {
            int input = visualizer.handleEvents();
            
            if (input == 2) {
                manual_mode = !manual_mode;
                std::cout << (manual_mode ? "Switched to manual mode" : "Switched to Q-learning mode") << std::endl;
            }

            int action;
            if (manual_mode) {
                if (input == 0 || input == 1) {
                    action = input;
                } else {
                    action = -1;  // No action if no key pressed
                }
            } else {
                action = q_learning.choose_action(cart_pole);
            }

            if (action != -1) {
                CartPole old_state = cart_pole;
                done = !cart_pole.step(action);
                
                if (!manual_mode) {
                    double reward = done ? -1.0 : 0.1;  // Penalize for falling, small reward for staying up
                    q_learning.update_q_table(old_state, action, reward, cart_pole);
                }

                ++step;
            }

            visualizer.render(cart_pole);
        }

        episode_lengths.push_back(step);
        std::cout << "Episode " << episode + 1 << " finished after " << step << " steps." << std::endl;

        // Print average episode length over last 100 episodes
        if (episode % 100 == 0 && episode > 0) {
            double avg_length = std::accumulate(episode_lengths.end() - 100, episode_lengths.end(), 0.0) / 100.0;
            std::cout << "Average episode length over last 100 episodes: " << avg_length << std::endl;
        }

        if (manual_mode) {
            std::cout << "Press 'M' to switch back to Q-learning mode" << std::endl;
            while (manual_mode && visualizer.isOpen()) {
                int input = visualizer.handleEvents();
                if (input == 2) {
                    manual_mode = false;
                    std::cout << "Switched to Q-learning mode" << std::endl;
                }
            }
        }
    }

    return 0;
}
