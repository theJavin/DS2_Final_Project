#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

// Constants
const float TIMESTEP = 1.0f / 60.0f;
const int VELOCITY_ITERATIONS = 6;
const int POSITION_ITERATIONS = 2;
const float SCALE = 100.0f; // pixels per meter
const float VIEW_WIDTH = 10.0f; // view width in meters
const float VIEW_HEIGHT = 7.5f; // view height in meters
const float RAIL_LENGTH = 8.0f; // length of the rail in meters
const float RAIL_LIMIT = 3.5f; // distance from center to rail limit

class CartPole {
private:
    b2World* world;
    b2Body* ground;
    b2Body* cart;
    b2Body* pole;
    b2Body* leftLimit;
    b2Body* rightLimit;
    b2RevoluteJoint* poleJoint;
    b2PrismaticJoint* cartJoint;

public:
    CartPole() {
        // Create the world with gravity
        world = new b2World(b2Vec2(0.0f, -9.8f));

        // Create the ground
        b2BodyDef groundDef;
        groundDef.position.Set(0.0f, 0.5f);
        ground = world->CreateBody(&groundDef);

        b2EdgeShape groundShape;
        groundShape.SetTwoSided(b2Vec2(-RAIL_LENGTH/2, 0.0f), b2Vec2(RAIL_LENGTH/2, 0.0f));
        ground->CreateFixture(&groundShape, 0.0f);

        // Create rail limits
        b2BodyDef limitDef;
        limitDef.position.Set(-RAIL_LIMIT, 0.75f);
        leftLimit = world->CreateBody(&limitDef);

        limitDef.position.Set(RAIL_LIMIT, 0.75f);
        rightLimit = world->CreateBody(&limitDef);

        b2PolygonShape limitShape;
        limitShape.SetAsBox(0.1f, 0.25f);

        b2FixtureDef limitFixture;
        limitFixture.shape = &limitShape;
        limitFixture.density = 0.0f;
        limitFixture.restitution = 0.2f; // Add a little bounce

        leftLimit->CreateFixture(&limitFixture);
        rightLimit->CreateFixture(&limitFixture);

        // Create the cart
        b2BodyDef cartDef;
        cartDef.type = b2_dynamicBody;
        cartDef.position.Set(0.0f, 1.0f);
        cart = world->CreateBody(&cartDef);

        b2PolygonShape cartShape;
        cartShape.SetAsBox(0.5f, 0.25f);

        b2FixtureDef cartFixture;
        cartFixture.shape = &cartShape;
        cartFixture.density = 1.0f;
        cartFixture.friction = 0.3f;
        cartFixture.restitution = 0.1f; // Add a little bounce
        cart->CreateFixture(&cartFixture);

        // Create the pole
        b2BodyDef poleDef;
        poleDef.type = b2_dynamicBody;
        poleDef.position.Set(0.0f, 2.5f);
        pole = world->CreateBody(&poleDef);

        b2PolygonShape poleShape;
        poleShape.SetAsBox(0.05f, 0.5f);

        b2FixtureDef poleFixture;
        poleFixture.shape = &poleShape;
        poleFixture.density = 1.0f;
        pole->CreateFixture(&poleFixture);

        // Create the revolute joint between cart and pole
        b2RevoluteJointDef poleJointDef;
        poleJointDef.bodyA = cart;
        poleJointDef.bodyB = pole;
        poleJointDef.localAnchorA.Set(0.0f, 0.25f);
        poleJointDef.localAnchorB.Set(0.0f, -0.5f);
        poleJointDef.enableLimit = false;

        poleJoint = (b2RevoluteJoint*)world->CreateJoint(&poleJointDef);

        // Create prismatic joint to constrain cart to horizontal movement
        b2PrismaticJointDef cartJointDef;
        cartJointDef.Initialize(ground, cart, cart->GetPosition(), b2Vec2(1.0f, 0.0f));
        cartJointDef.enableLimit = true;
        cartJointDef.lowerTranslation = -RAIL_LIMIT - 0.5f;
        cartJointDef.upperTranslation = RAIL_LIMIT + 0.5f;

        cartJoint = (b2PrismaticJoint*)world->CreateJoint(&cartJointDef);
    }

    void step() {
        world->Step(TIMESTEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    }

    void applyForce(float force) {
        cart->ApplyForceToCenter(b2Vec2(force, 0.0f), true);
    }

    void render(sf::RenderWindow& window, const sf::View& view) {
        // Render ground
        sf::RectangleShape groundShape(sf::Vector2f(RAIL_LENGTH * SCALE, 0.1f * SCALE));
        groundShape.setOrigin(RAIL_LENGTH/2 * SCALE, 0.05f * SCALE);
        groundShape.setPosition(0, view.getSize().y - 0.5f * SCALE);
        groundShape.setFillColor(sf::Color::Black);
        window.draw(groundShape);

        // Render rail limits
        sf::RectangleShape leftLimitShape(sf::Vector2f(0.2f * SCALE, 0.5f * SCALE));
        leftLimitShape.setOrigin(0.1f * SCALE, 0.25f * SCALE);
        leftLimitShape.setPosition(-RAIL_LIMIT * SCALE, view.getSize().y - 0.75f * SCALE);
        leftLimitShape.setFillColor(sf::Color::Red);
        window.draw(leftLimitShape);

        sf::RectangleShape rightLimitShape(sf::Vector2f(0.2f * SCALE, 0.5f * SCALE));
        rightLimitShape.setOrigin(0.1f * SCALE, 0.25f * SCALE);
        rightLimitShape.setPosition(RAIL_LIMIT * SCALE, view.getSize().y - 0.75f * SCALE);
        rightLimitShape.setFillColor(sf::Color::Red);
        window.draw(rightLimitShape);

        // Render cart
        sf::RectangleShape cartShape(sf::Vector2f(1.0f * SCALE, 0.5f * SCALE));
        cartShape.setOrigin(0.5f * SCALE, 0.25f * SCALE);
        cartShape.setPosition(cart->GetPosition().x * SCALE, view.getSize().y - cart->GetPosition().y * SCALE);
        cartShape.setFillColor(sf::Color::Blue);
        window.draw(cartShape);

        // Render pole
        sf::RectangleShape poleShape(sf::Vector2f(0.1f * SCALE, 1.0f * SCALE));
        poleShape.setOrigin(0.05f * SCALE, 0.5f * SCALE);
        poleShape.setPosition(pole->GetPosition().x * SCALE, view.getSize().y - pole->GetPosition().y * SCALE);
        poleShape.setRotation(-pole->GetAngle() * 180 / M_PI);
        poleShape.setFillColor(sf::Color::Green);
        window.draw(poleShape);
    }

    b2Vec2 getCartPosition() const {
        return cart->GetPosition();
    }

    ~CartPole() {
        delete world;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cart Pole Simulation");
    window.setFramerateLimit(60);

    // Create a view for our camera
    sf::View view(sf::FloatRect(0, 0, VIEW_WIDTH * SCALE, VIEW_HEIGHT * SCALE));
    view.setCenter(0, VIEW_HEIGHT * SCALE / 2);
    window.setView(view);

    CartPole cartPole;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (clock.getElapsedTime().asSeconds() >= TIMESTEP) {
            // Apply a small random force to the cart
            float force = (rand() % 100 - 50) * 0.1f;
            cartPole.applyForce(force);

            cartPole.step();
            clock.restart();
        }

        // Update the view to follow the cart
        b2Vec2 cartPos = cartPole.getCartPosition();
        view.setCenter(cartPos.x * SCALE, VIEW_HEIGHT * SCALE / 2);
        window.setView(view);

        window.clear(sf::Color::White);
        cartPole.render(window, view);
        window.display();
    }

    return 0;
}