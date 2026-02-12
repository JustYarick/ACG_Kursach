#include "Renderer.h"
#include <glad/glad.h>
#include <vector>
#include <cmath>
#include <glm/gtc/type_ptr.hpp>

static const char *vertexSrc = R"(
#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 offset;
uniform float radius;

void main()
{
    vec2 pos = aPos * radius + offset;
    gl_Position = vec4(pos, 0.0, 1.0);
}
)";

static const char *fragmentSrc = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.8, 0.3, 0.3, 1.0);
}
)";

unsigned int CompileShader(unsigned int type, const char *src) {
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);
  return shader;
}

unsigned int Renderer::CreateShader() {
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSrc);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

  unsigned int program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

void Renderer::CreateCircleMesh() {
  std::vector<float> vertices;
  int segments = 40;

  vertices.push_back(0.0f);
  vertices.push_back(0.0f);

  for (int i = 0; i <= segments; i++) {
    float angle = 2.0f * 3.1415926f * i / segments;
    vertices.push_back(cos(angle));
    vertices.push_back(sin(angle));
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

void Renderer::Init() {
  shaderProgram = CreateShader();
  CreateCircleMesh();
}

void Renderer::DrawCircle(const Body &body) {
  glUseProgram(shaderProgram);

  glUniform2fv(glGetUniformLocation(shaderProgram, "offset"), 1,
               glm::value_ptr(body.position));

  glUniform1f(glGetUniformLocation(shaderProgram, "radius"), body.radius);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 42);
}

void Renderer::Shutdown() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
}
