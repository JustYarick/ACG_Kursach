#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
  Shader(const std::string &vertexPath, const std::string &fragmentPath);

  void Use() const;

  void SetMat4(const std::string &name, const glm::mat4 &value) const;
  void SetVec2(const std::string &name, const glm::vec2 &value) const;
  void SetVec3(const std::string &name, const glm::vec3 &value) const;
  void SetFloat(const std::string &name, float value) const;

  unsigned int ID;
};
