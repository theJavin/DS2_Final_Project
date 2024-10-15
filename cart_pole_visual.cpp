#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <random>

class CartPole {
private:
    double x, x_dot, theta, theta_dot;
    const double gravity = 9.8;
    const double mass_cart = 1.0;
    const double mass_pole = 0.1;
    const double total_mass = mass_cart + mass_pole;
    const double length = 0.5;
    const double force_mag = 10.0;
    const double tau = 0.02;
    const double x_boundary = 4.0;
    const double theta_boundary = M_PI / 2.5; // 30 degrees (pi/6 radians)

public:
    CartPole() : x(0), x_dot(0), theta(0), theta_dot(0) {}

    void reset() {
        x = 0;
        x_dot = 0;
        theta = 0;
        theta_dot = 0;
    }

    bool step(int action) {
        double force = action == 1 ? force_mag : -force_mag;
        double costheta = std::cos(theta);
        double sintheta = std::sin(theta);

        double temp = (force + mass_pole * length * theta_dot * theta_dot * sintheta) / total_mass;
        double thetaacc = (gravity * sintheta - costheta * temp) / (length * (4.0 / 3.0 - mass_pole * costheta * costheta / total_mass));
        double xacc = temp - mass_pole * length * thetaacc * costheta / total_mass;

        x += tau * x_dot;
        x_dot += tau * xacc;
        theta += tau * theta_dot;
        theta_dot += tau * thetaacc;

        return std::abs(x) < x_boundary && std::abs(theta) < theta_boundary;
    }

    double getX() const { return x; }
    double getTheta() const { return theta; }
    double getXBoundary() const { return x_boundary; }
    double getThetaBoundary() const { return theta_boundary; }
};

class Visualizer {
private:
    sf::RenderWindow window;
    const float scale = 80.0f;
    const float cart_width = 80.0f;
    const float cart_height = 40.0f;
    const float pole_length = 100.0f;
    const float pole_thickness = 10.0f;

public:
    Visualizer() : window(sf::VideoMode(800, 400), "Cart Pole Simulation") {
        window.setFramerateLimit(60);
    }

    void render(const CartPole& cart_pole) {
        window.clear(sf::Color::White);

        // Calculate cart position
        float cart_center_x = 400 + cart_pole.getX() * scale;

        // Draw boundaries
        sf::RectangleShape leftBoundary(sf::Vector2f(5, 400));
        leftBoundary.setFillColor(sf::Color::Red);
        leftBoundary.setPosition(400 - cart_pole.getXBoundary() * scale, 0);
        window.draw(leftBoundary);

        sf::RectangleShape rightBoundary(sf::Vector2f(5, 400));
        rightBoundary.setFillColor(sf::Color::Red);
        rightBoundary.setPosition(400 + cart_pole.getXBoundary() * scale, 0);
        window.draw(rightBoundary);

        // Draw angle limits
        sf::ConvexShape leftAngleLimit;
        leftAngleLimit.setPointCount(3);
        leftAngleLimit.setPoint(0, sf::Vector2f(cart_center_x, 300));
        leftAngleLimit.setPoint(1, sf::Vector2f(cart_center_x - pole_length * std::sin(cart_pole.getThetaBoundary()), 
                                                300 - pole_length * std::cos(cart_pole.getThetaBoundary())));
        leftAngleLimit.setPoint(2, sf::Vector2f(cart_center_x - pole_length * std::sin(cart_pole.getThetaBoundary()), 300));
        leftAngleLimit.setFillColor(sf::Color(255, 0, 0, 50)); // Semi-transparent red
        window.draw(leftAngleLimit);

        sf::ConvexShape rightAngleLimit;
        rightAngleLimit.setPointCount(3);
        rightAngleLimit.setPoint(0, sf::Vector2f(cart_center_x, 300));
        rightAngleLimit.setPoint(1, sf::Vector2f(cart_center_x + pole_length * std::sin(cart_pole.getThetaBoundary()), 
                                                 300 - pole_length * std::cos(cart_pole.getThetaBoundary())));
        rightAngleLimit.setPoint(2, sf::Vector2f(cart_center_x + pole_length * std::sin(cart_pole.getThetaBoundary()), 300));
        rightAngleLimit.setFillColor(sf::Color(255, 0, 0, 50)); // Semi-transparent red
        window.draw(rightAngleLimit);

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

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
};

int main() {
    CartPole cart_pole;
    Visualizer visualizer;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    while (visualizer.isOpen()) {
        cart_pole.reset();
        bool done = false;
        int step = 0;

        while (!done && step < 1000 && visualizer.isOpen()) {
            visualizer.handleEvents();
            visualizer.render(cart_pole);

            int action = dis(gen);
            done = !cart_pole.step(action);
            ++step;

            sf::sleep(sf::milliseconds(20)); // Slow down the simulation for visibility
        }

        std::cout << "Episode finished after " << step << " steps." << std::endl;
    }

    return 0;
}