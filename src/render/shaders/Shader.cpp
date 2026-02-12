#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

static std::string ReadFile(const std::string &path) {
  std::ifstream file(path);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

static unsigned int Compile(unsigned int type, const std::string &src) {
  unsigned int shader = glCreateShader(type);
  const char *code = src.c_str();
  glShaderSource(shader, 1, &code, nullptr);
  glCompileShader(shader);
  return shader;
}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
  std::string vCode = ReadFile(vertexPath);
  std::string fCode = ReadFile(fragmentPath);

  unsigned int vs = Compile(GL_VERTEX_SHADER, vCode);
  unsigned int fs = Compile(GL_FRAGMENT_SHADER, fCode);

  ID = glCreateProgram();
  glAttachShader(ID, vs);
  glAttachShader(ID, fs);
  glLinkProgram(ID);

  glDeleteShader(vs);
  glDeleteShader(fs);
}

void Shader::Use() const { glUseProgram(ID); }

void Shader::SetMat4(const std::string &name, const glm::mat4 &value) const {
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &value[0][0]);
}

void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::SetFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
