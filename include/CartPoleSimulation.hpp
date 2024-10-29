
// CartPoleSimulation.hpp
#pragma once
#include "PhysicsSystem.hpp"
#include "Renderer.hpp"

class CartPoleSimulation {
public:
    CartPoleSimulation();
    void run();

private:
    PhysicsSystem physics;
    Renderer renderer;
    static constexpr float FORCE_MAGNITUDE = 5.0f;
    
    float handleInput();
};
