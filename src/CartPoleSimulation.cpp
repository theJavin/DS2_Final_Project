
// CartPoleSimulation.cpp
#include "CartPoleSimulation.hpp"

CartPoleSimulation::CartPoleSimulation() : physics(), renderer() {}

void CartPoleSimulation::run() {
    while (!renderer.shouldClose()) {
        float force = handleInput();
        physics.applyForce(force);
        physics.update();
        renderer.render(physics.getBodies());
        glfwPollEvents();
    }
}

float CartPoleSimulation::handleInput() {
    float force = 0.0f;
    auto* window = renderer.getWindow();
    
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        force = -FORCE_MAGNITUDE;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        force = FORCE_MAGNITUDE;
    }
    return force;
}
