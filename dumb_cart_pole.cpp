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

        return std::abs(x) < 2.4 && std::abs(theta) < 0.2095;
    }

    void render() {
        std::cout << "Cart position: " << x << ", Pole angle: " << theta << std::endl;
    }
};

int main() {
    CartPole env;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int episode = 0; episode < 10; ++episode) {
        env.reset();
        bool done = false;
        int step = 0;

        while (!done && step < 200) {
            env.render();
            int action = dis(gen);
            done = !env.step(action);
            ++step;
        }

        std::cout << "Episode " << episode + 1 << " finished after " << step << " steps." << std::endl;
    }

    return 0;
}