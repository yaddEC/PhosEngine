// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------


#define INPUT_EXPORTS
#include "Engine/Input.hpp"

using namespace Maths;
using namespace Engine;

#include <iostream>
#include "Wrapper/Window.hpp"

float Input::deltaTime = 0.0f;




void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::GetInstance().ScrollBackDoor(yoffset);
}

void Input::Init(GLFWwindow* _window)
{
	mouseMap = 0;
	timeStep = 1.f ;
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

void Input::Update() {

	//deltaTime 


		auto currentFrameTime = Wrapper::Window::GetTime();
		static auto lastFrameTime = Wrapper::Window::GetTime();
		float temp = currentFrameTime - lastFrameTime;
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
	mouseDelta.x = mousePosX - mousePosition.x;
	mouseDelta.y = mousePosY - mousePosition.y;

	mousePosition.x = mousePosX;
	mousePosition.y = mousePosY;

	//DisplayGUI();
	anyKeyDown = false;
	for (size_t i = 0; i < 348; i++) {
		if (glfwGetKey(window, i) == GLFW_PRESS) {
			if (keyMap[i] == 0) { keyMap[i] = 2; anyKeyDown = true; }
			else keyMap[i] = 1;
		}
		if (glfwGetKey(window, i) == GLFW_RELEASE) {
			keyMap[i] = 0;
		}
	}

}

bool Input::IsKeyPressed(int key) {
	return keyMap[key] > 0;
}

bool Input::IsKeyDown(int key) {
	return keyMap[key] == 2;
}

bool Input::IsAnyKeyDown() {
	return anyKeyDown;
}


bool Input::IsMouseButtonPressed(int mouseButton) {
	
	bool mouseBool = glfwGetMouseButton(window, mouseButton);
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

	return false;

}

bool Input::IsMouseButtonDown(int mouseButton) {
	
	return glfwGetMouseButton(window, mouseButton);

}

bool Input::IsMouseButtonReleased(int mouseButton) {

	bool mouseBool = glfwGetMouseButton(window, mouseButton);
	if (!mouseBool)
	{
		if (mouseMap == 1)
		{
			mouseMap = 0;
			return true;
		}

	}
	else
	{
		mouseMap = 1;
	}
	return false;

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
