#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"



class Application
{
public:

	Application()
		:io(GetIO()) {}

	void Init();
	void Run();
	void Close();

	GLFWwindow* GetWindow() const { return window; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

private:

	//class Scene* mainScene; // TEMP : load scene eventually
	//class SceneWindow* sceneWindow;
	//class AssetsExplorer* assetsExplorer;

	ImGuiIO& io;

	int width, height;
	GLFWwindow* window;


	ImGuiIO& GetIO()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		return ImGui::GetIO();
	}
};
