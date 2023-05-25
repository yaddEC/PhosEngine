// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------


#include "Engine/Input.hpp"

using namespace Maths;
using namespace Engine;

#include <iostream>
#include "Wrapper/Window.hpp"

float Input::deltaTime = 0.0f;




void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::GetInstance().ScrollBackDoor(static_cast<int>(yoffset));
}

void Input::Init(GLFWwindow* _window)
{
	timeStep = 1/60.f ;
	window = _window;
	for (size_t i = 0; i < 348; i++) {
		keyMap[i] = 0;
	}
	glfwSetScrollCallback(window, scroll_callback);
}

void Input::ScrollBackDoor(int value)
{
	scrollDelta = value;
}

float Input::GetHorizontalAxis() {
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		return 1;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		return -1;

	return 0;
}

float Input::GetVerticalAxis() {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		return 1;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		return -1;

	return 0;
}

Vec2 Input::GetMouseDelta() {
	return mouseDelta;
}

void Input::Update()
{

	auto currentFrameTime = Wrapper::Window::GetTime();
	static auto lastFrameTime = Wrapper::Window::GetTime();
	float temp = static_cast<float>(currentFrameTime - lastFrameTime);
	if (temp> timeStep)//
	{
		deltaTime = timeStep;
	}
	else
	{
		deltaTime = temp;
	}
		
	lastFrameTime = currentFrameTime;

	double mousePosX, mousePosY;
	glfwGetCursorPos(window, &mousePosX, &mousePosY);
	mouseDelta.x = static_cast<float>(mousePosX - mousePosition.x);
	mouseDelta.y = static_cast<float>(mousePosY - mousePosition.y);

	mousePosition.x = static_cast<float>(mousePosX);
	mousePosition.y = static_cast<float>(mousePosY);

	//DisplayGUI();
	anyKeyDown = false;
	for (int i = 0; i < 348; i++) {
		if (glfwGetKey(window, i) == GLFW_PRESS) {
			if (keyMap[i] == 0) { keyMap[i] = 2; anyKeyDown = true; }
			else keyMap[i] = 1;
		}
		if (glfwGetKey(window, i) == GLFW_RELEASE) {
			if (keyMap[i] > 0)
				keyMap[i] = -1;
			else
				keyMap[i] = 0;
		}
	}

	for (int i = 0; i < 3; i++) {
		if (glfwGetMouseButton(window, i) == GLFW_PRESS) {
			if (mouseMap[i] == 0) { mouseMap[i] = 2; }
			else mouseMap[i] = 1;
		}
		if (glfwGetMouseButton(window, i) == GLFW_RELEASE) {
			if(mouseMap[i] > 0)
				mouseMap[i] = -1;
			else
				mouseMap[i] = 0;
		}
	}

}

bool Input::IsKeyPressed(int key) {
	return keyMap[key] > 0;
}

bool Input::IsKeyDown(int key) {
	return keyMap[key] == 2;
}

bool Engine::Input::IsKeyReleased(int key)
{
	return keyMap[key] == -1;
}

bool Input::IsAnyKeyDown() {
	return anyKeyDown;
}


bool Input::IsMouseButtonPressed(int mouseButton) {
	
	/*bool mouseBool = glfwGetMouseButton(window, mouseButton);
	if (mouseBool)
	{
		if (mouseMap == 0)
		{
			mouseMap = 1;
			return true;
		}
	}
	else
	{
		mouseMap = 0;
	}

	return false;*/
	return mouseMap[mouseButton] > 0;
}

bool Input::IsMouseButtonDown(int mouseButton) {
	
	return mouseMap[mouseButton] == 2;

}

bool Engine::Input::IsMouseButtonReleased(int mouseButton)
{
	return mouseMap[mouseButton] == -1;
}

bool Engine::Input::IsMouseButtonUp(int mouseButton)
{
	return mouseMap[mouseButton] == 0;
}



int Input::GetScrollDelta()
{
	int temp = scrollDelta;
	scrollDelta = 0;
	return temp;
}

void Input::DisplayGUI() {
	/*ImGui::Begin("Input");

	ImGui::Text(("Vertical axis : " + std::to_string((int)GetVerticalAxis())).c_str());
	ImGui::Text(("Horizontal axis : " + std::to_string((int)GetHorizontalAxis())).c_str());
	ImGui::Text(("Mouse delta : (" + std::to_string((int)GetMouseDelta().x) + " ; " + std::to_string((int)GetMouseDelta().y) + ")").c_str());

	for (int i = 0; i < 348; i++) {
		ImGui::Text(("key " + to_string(i) + " : " + to_string(keyMap[i])).c_str());
	}

	ImGui::End();*/
}
