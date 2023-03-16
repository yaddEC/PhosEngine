// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------


#include "imgui.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Resource/Texture.hpp"

#include "LowRenderer/Framebuffer.hpp"

#define GUI_EXPORTS
#include "GUI/GUI.hpp"

bool GUI::InitGUI(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	// Set up ImGui
	ImGuiIO& io = ImGui::GetIO();

	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	return true;
}

void GUI::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUI::RenderFrame(GLFWwindow* window)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0, 0.2f, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	ImGui::EndFrame();
}

void GUI::DestroyGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}


bool GUI::BeginWindow(const std::string& name, bool canCollpase)
{
	return ImGui::Begin(name.c_str(), 0, ImGuiWindowFlags_NoCollapse);
}

void GUI::EndWindow()
{
	ImGui::End();
}

void GUI::DockingSpace()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::DockSpaceOverViewport(viewport);
}

Maths::Vec2 GUI::GetWindowSize()
{
	return Maths::Vec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
}

bool GUI::IsWondowFocused()
{
	return ImGui::IsWindowFocused();
}

void GUI::Image(const Resource::Texture& texture, Maths::Vec2 size)
{
	ImGui::Image((ImTextureID)texture.GetTextureKey(), ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
}

bool GUI::EditFloat(const std::string& label, float& value, float speed, float min, float max)
{
	return ImGui::DragFloat(label.c_str(), &value, speed, min, max);
}

bool GUI::EditVec2(const std::string& label, Maths::Vec2& value, float speed, float min, float max)
{
	return ImGui::DragFloat2(label.c_str(), &value.x, speed, min, max);
}

bool GUI::EditVec3(const std::string& label, Maths::Vec3& value, float speed, float min, float max)
{
	return ImGui::DragFloat3(label.c_str(), &value.x, speed, min, max);
}

bool GUI::EditColorRGB(const std::string& label, Maths::Vec3& value)
{
	return ImGui::ColorEdit3(label.c_str(), &value.x);
}

bool GUI::EditColorRGBA(const std::string& label, Maths::Vec4& value)
{
	return ImGui::ColorEdit4(label.c_str(), &value.x);
}

void GUI::DisplayText(const std::string& text)
{
	ImGui::Text(text.c_str());
}

void GUI::DisplayFloat(const std::string& label, float value)
{
	return ImGui::Text((label + " : " + std::to_string(value)).c_str());
}

void GUI::DisplayVec2(const std::string& label, const Maths::Vec2& value)
{
	return ImGui::Text((label + " : (" + std::to_string(value.x) + ", " + std::to_string(value.y) + ")").c_str());
}

void GUI::DisplayVec3(const std::string& label, const Maths::Vec3& value)
{
	return ImGui::Text((label + " : (" + std::to_string(value.x) + ", " + std::to_string(value.y) + ", " + std::to_string(value.z) + ")").c_str());
}
