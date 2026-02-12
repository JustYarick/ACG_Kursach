#include "Renderer.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cmath>

void Renderer::Init() {
  circleShader = std::make_unique<Shader>("assets/shaders/circle.vert",
                                          "assets/shaders/circle.frag");

  CreateCircleMesh();
}

void Renderer::SetProjection(float width, float height) {
  float aspect = width / height;
  projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f);
}

void Renderer::CreateCircleMesh() {
  std::vector<float> vertices;
  const int segments = 40;

  vertices.push_back(0.0f);
  vertices.push_back(0.0f);

  for (int i = 0; i <= segments; ++i) {
    float angle = 2.0f * 3.1415926f * i / segments;
    vertices.push_back(std::cos(angle));
    vertices.push_back(std::sin(angle));
  }

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
}

Shader *Renderer::GetDefaultShader() { return circleShader.get(); }

void Renderer::Draw(const Body &body) {
  if (!body.shader)
    return;

  body.shader->Use();
  body.shader->SetMat4("projection", projection);
  body.shader->SetVec2("offset", body.position);
  body.shader->SetFloat("radius", body.radius);
  body.shader->SetVec3("color", body.color);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 42);
}

void Renderer::Shutdown() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}
