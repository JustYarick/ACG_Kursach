#include "UI.h"
#include "Config.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

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

void UI::Render(Config &config) {
  ImGui::Begin("Simulation Settings");

  ImGui::SeparatorText("Physics");

  ImGui::SliderFloat("Restitution (e)", &config.restitution, 0.0f, 1.0f);
  ImGui::SliderFloat("Mass 1", &config.mass1, 0.1f, 10.0f);
  ImGui::SliderFloat("Mass 2", &config.mass2, 0.1f, 10.0f);

  ImGui::SliderFloat("Velocity 1", &config.velocity1, -10.0f, 10.0f);
  ImGui::SliderFloat("Velocity 2", &config.velocity2, -10.0f, 10.0f);

  ImGui::SeparatorText("Mode");

  ImGui::Checkbox("3D Mode", &config.is3D);
  ImGui::Checkbox("Run Simulation", &config.simulationRunning);

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
