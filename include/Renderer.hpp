
// Renderer.hpp
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "PhysicsSystem.hpp"

class Renderer {
public:
    Renderer(int width = 1024, int height = 768);
    ~Renderer();
    
    void render(const PhysicsSystem::Bodies& bodies);
    bool shouldClose() const;
    GLFWwindow* getWindow() const { return window; }

private:
    GLFWwindow* window;
    GLuint shaderProgram;
    GLuint VAO, VBO;
    
    void initGL();
    void setupShaders();
    void setupGeometry();
    void drawGround();
    void drawBody(b2Body* body, const glm::vec3& color, 
                 float width, float height);
};