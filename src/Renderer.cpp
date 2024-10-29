
// Renderer.cpp
#include "Renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer(int width, int height) {
    initGL();
    setupShaders();
    setupGeometry();
    
    // Set up viewport
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);
}

void Renderer::initGL() {
    if (!glfwInit()) throw std::runtime_error("Failed to init GLFW");
    
    window = glfwCreateWindow(1024, 768, "CartPole", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }
    
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to init GLEW");
    }
}

void Renderer::setupShaders() {
    // Shader setup code remains the same as original
    // ... (omitted for brevity, copy from original)
}

void Renderer::setupGeometry() {
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

void Renderer::render(const PhysicsSystem::Bodies& bodies) {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    
    // Set up view and projection matrices
    auto view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    auto projection = glm::ortho(-10.0f, 10.0f, -7.5f, 7.5f, 0.1f, 100.0f);
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, 
                       glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE,
                       glm::value_ptr(projection));
    
    drawGround();
    drawBody(bodies.cart, glm::vec3(0.2f, 0.3f, 0.8f), 1.0f, 0.5f);
    drawBody(bodies.pole, glm::vec3(0.8f, 0.3f, 0.2f), 0.1f, 2.0f);
    
    glfwSwapBuffers(window);
}

void Renderer::drawGround() {
    auto transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f));
    transform = glm::scale(transform, glm::vec3(20.0f, 0.1f, 1.0f));
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE,
                       glm::value_ptr(transform));
    glUniform3f(glGetUniformLocation(shaderProgram, "color"), 0.5f, 0.5f, 0.5f);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Renderer::drawBody(b2Body* body, const glm::vec3& color, 
                       float width, float height) {
    auto pos = body->GetPosition();
    auto angle = body->GetAngle();
    
    auto transform = glm::translate(glm::mat4(1.0f), 
                                  glm::vec3(pos.x, pos.y, 0.0f));
    transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(width, height, 1.0f));
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE,
                       glm::value_ptr(transform));
    glUniform3f(glGetUniformLocation(shaderProgram, "color"), 
                color.r, color.g, color.b);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

bool Renderer::shouldClose() const {
    return glfwWindowShouldClose(window);
}