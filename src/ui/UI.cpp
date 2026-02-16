#include "UI.h"
#include <string>
#include "Config.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include "core/Simulation.h"
#include "render/Renderer.h"
#include <glm/gtc/type_ptr.hpp>

void UI::Init(GLFWwindow *window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void UI::BeginFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void UI::Render(Config &config, Simulation &sim, Renderer &renderer) {
  ImGui::Begin("Simulation Settings");

  ImGui::SeparatorText("Physics");
  ImGui::SliderFloat("Restitution (e)", &config.restitution, 0.0f, 1.0f);

  ImGui::SeparatorText("Bodies");

  auto &bodies = sim.GetBodies();

  for (size_t i = 0; i < bodies.size(); ++i) {
    auto &body = bodies[i];

    ImGui::PushID((int)i);

    std::string label = "Body " + std::to_string(i);
    if (ImGui::TreeNode(label.c_str())) {
      ImGui::SliderFloat("Mass", &body.mass, 0.1f, 10.0f);
      ImGui::SliderFloat("Radius", &body.radius, 0.05f, 1.0f);

      ImGui::SliderFloat2("Velocity", glm::value_ptr(body.velocity), -5.0f,
                          5.0f);

      ImGui::SliderFloat2("Position", glm::value_ptr(body.position), -1.0f,
                          1.0f);

      ImGui::ColorEdit3("Color", glm::value_ptr(body.color));

      ImGui::TreePop();
    }

    ImGui::PopID();
  }

  if (ImGui::Button("Add Body")) {
    Body newBody(1.0f, 0.1f, {0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f});
    newBody.shader = renderer.GetDefaultShader();
    sim.AddBody(newBody);
  }

  ImGui::SeparatorText("Simulation");

  if (ImGui::Button("Reset")) {
    sim.Reset(config);
  }

  ImGui::SameLine();
  ImGui::Checkbox("Run", &config.simulationRunning);

  ImGui::SeparatorText("Statistics");

  ImGui::Text("Energy: %.3f", sim.GetTotalEnergy());

  glm::vec2 momentum = sim.GetTotalMomentum();
  ImGui::Text("Momentum: (%.3f, %.3f)", momentum.x, momentum.y);

  for (size_t i = 0; i < bodies.size(); ++i) {
    const auto &body = bodies[i];

    float energy =
        0.5f * body.mass *
        (body.velocity.x * body.velocity.x + body.velocity.y * body.velocity.y);

    ImGui::Text("Body %zu | m=%.2f r=%.2f | "
                "pos(%.2f, %.2f) | "
                "vel(%.2f, %.2f) | "
                "E=%.3f",
                i, body.mass, body.radius, body.position.x, body.position.y,
                body.velocity.x, body.velocity.y, energy);
  }

  ImGui::SeparatorText("Visual");
  ImGui::ColorEdit3("Background", config.clearColor);

  ImGui::End();
}

void UI::EndFrame() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::Shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
