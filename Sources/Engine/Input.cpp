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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::GetInstance().ScrollBackDoor(yoffset);
}

void Input::Init(GLFWwindow* _window)
{
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
	return glfwGetMouseButton(window, mouseButton);
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
