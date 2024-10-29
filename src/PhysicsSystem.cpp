
// PhysicsSystem.cpp
#include "PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem(float gravity) {
    world = new b2World(b2Vec2(0.0f, gravity));
    createGround();
    createCart();
    createPole();
    createJoints();
}

PhysicsSystem::~PhysicsSystem() {
    delete world;
}

void PhysicsSystem::createGround() {
    b2BodyDef groundDef;
    groundDef.position.Set(0.0f, -2.0f);
    b2Body* ground = world->CreateBody(&groundDef);
    
    b2EdgeShape groundShape;
    groundShape.SetTwoSided(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));
    ground->CreateFixture(&groundShape, 0.0f);
}

void PhysicsSystem::createCart() {
    b2BodyDef cartDef;
    cartDef.type = b2_dynamicBody;
    cartDef.position.Set(0.0f, 0.0f);
    cartDef.linearDamping = 0.5f;
    bodies.cart = world->CreateBody(&cartDef);
    
    b2PolygonShape cartShape;
    cartShape.SetAsBox(0.5f, 0.25f);  // Half-width and half-height
    
    b2FixtureDef cartFixture;
    cartFixture.shape = &cartShape;
    cartFixture.density = 1.0f;
    cartFixture.friction = 0.3f;
    bodies.cart->CreateFixture(&cartFixture);
}

void PhysicsSystem::createPole() {
    b2BodyDef poleDef;
    poleDef.type = b2_dynamicBody;
    poleDef.position.Set(0.0f, 1.0f);  // Half pole length
    poleDef.angularDamping = 0.05f;
    bodies.pole = world->CreateBody(&poleDef);
    
    b2PolygonShape poleShape;
    poleShape.SetAsBox(0.05f, 1.0f);  // Half-width and half-length
    
    b2FixtureDef poleFixture;
    poleFixture.shape = &poleShape;
    poleFixture.density = 1.0f;
    poleFixture.friction = 0.3f;
    bodies.pole->CreateFixture(&poleFixture);
}

void PhysicsSystem::createJoints() {
    // Cart constraint
    b2PrismaticJointDef prismaticDef;
    prismaticDef.Initialize(world->GetGroundBody(), bodies.cart, 
                          bodies.cart->GetPosition(), b2Vec2(1.0f, 0.0f));
    prismaticDef.enableLimit = true;
    prismaticDef.lowerTranslation = -10.0f;
    prismaticDef.upperTranslation = 10.0f;
    world->CreateJoint(&prismaticDef);
    
    // Pole joint
    b2RevoluteJointDef revoluteDef;
    revoluteDef.Initialize(bodies.cart, bodies.pole, b2Vec2(0.0f, 0.0f));
    bodies.joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteDef);
}

void PhysicsSystem::update(float timeStep) {
    world->Step(timeStep, 6, 2);
}

void PhysicsSystem::applyForce(float force) {
    bodies.cart->ApplyForceToCenter(b2Vec2(force, 0.0f), true);
}
