// PhysicsSystem.hpp
#pragma once
#include <box2d/box2d.h>

class PhysicsSystem {
public:
    struct Bodies {
        b2Body* cart;
        b2Body* pole;
        b2RevoluteJoint* joint;
    };

    PhysicsSystem(float gravity = -9.81f);
    ~PhysicsSystem();
    
    void update(float timeStep = 1.0f/60.0f);
    void applyForce(float force);
    Bodies& getBodies() { return bodies; }

private:
    b2World* world;
    Bodies bodies;
    
    void createGround();
    void createCart();
    void createPole();
    void createJoints();
};