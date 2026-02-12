#include "UI.h"
#include "Config.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include "core/Simulation.h"
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

void UI::Render(Config &config, Simulation &sim) {
  ImGui::Begin("Simulation Settings");

  ImGui::SeparatorText("Physics");

  ImGui::SliderFloat("Restitution (e)", &config.restitution, 0.0f, 1.0f);

  ImGui::SliderFloat("Mass 1", &config.mass1, 0.1f, 10.0f);
  ImGui::SliderFloat("Mass 2", &config.mass2, 0.1f, 10.0f);

  ImGui::SeparatorText("Initial Conditions");

  ImGui::SliderFloat2("Velocity 1", glm::value_ptr(config.velocity1), -5.0f,
                      5.0f);
  ImGui::SliderFloat2("Velocity 2", glm::value_ptr(config.velocity2), -5.0f,
                      5.0f);

  ImGui::SliderFloat2("Position 1", glm::value_ptr(config.position1), -1.0f,
                      1.0f);
  ImGui::SliderFloat2("Position 2", glm::value_ptr(config.position2), -1.0f,
                      1.0f);

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
