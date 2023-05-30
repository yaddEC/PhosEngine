// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include "Engine/Input.hpp"

#include "Wrapper/Window.hpp"
#include "Wrapper/GUI.hpp"

#include <iostream>

using namespace Maths;
using namespace Engine;



void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::GetInstance().ScrollBackDoor(static_cast<int>(yoffset));
}

void Input::Init(GLFWwindow* _window)
{
	timeStep = 1/60.f ;
	deltaTime = 0.0f;
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

float Engine::Input::GetGamepadAxis(int axis, int idPlayer)
{
	return GpInput[idPlayer].axis[axis];
}

Vec2 Input::GetMouseDelta() 
{
	return mouseDelta;
}

void Input::Update()
{
	UpdateGamePad();
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

void Input::UpdateGamePad()
{
	for (int i = 0; i < 2; i++)
	{
		if (glfwJoystickPresent(i))
		{
			int axisCount;
			GpInput[i].IDconnexion = i;
			const float* ptr = glfwGetJoystickAxes(GpInput[i].IDconnexion, &axisCount);
			for (size_t j = 0; j < axisCount; j++)
			{
				GpInput[i].axis[j] = ptr[j];
				if (abs(GpInput[i].axis[j]) < 0.1)
				{
					GpInput[i].axis[j] = 0;
				}
			}

			int buttonCount;
			const unsigned char* buttons = glfwGetJoystickButtons(GpInput[i].IDconnexion, &buttonCount);
			for (int j = 0; j < 15; j++)
			{
				if (buttons[j] == GLFW_PRESS)
				{
					if (GpInput[i].button[j] == 0) { GpInput[i].button[j] = 2;}
					else GpInput[i].button[j] = 1;
				}
				if (buttons[j] == GLFW_RELEASE)
				{
					if (GpInput[i].button[j] > 0)
						GpInput[i].button[j] = -1;
					else
						GpInput[i].button[j] = 0;
				}
			}
		}
		else
		{
			GpInput[i].IDconnexion = -1;
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

bool Input::IsAnyKeyDown() 
{
	return anyKeyDown;
}

bool Input::IsButtonPressed(int key, int idPlayer)
{
	return GpInput[idPlayer].button[key] > 0;
}

bool Input::IsButtonDown(int key, int idPlayer) 
{
	return GpInput[idPlayer].button[key] == 2;
}

bool Engine::Input::IsButtonReleased(int key, int idPlayer)
{
	return GpInput[idPlayer].button[key] == -1;
}


bool Input::IsMouseButtonPressed(int mouseButton)
{
	return mouseMap[mouseButton] > 0;
}

bool Input::IsMouseButtonDown(int mouseButton)
{
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

void Input::DisplayGUI() 
{
	for (int i = 0; i < 2; i++)
	{			
		if (GpInput[i].IDconnexion != -1)
		{
			if (Wrapper::GUI::CollapsingHeader(("Gamepad " + std::to_string(GpInput[i].IDconnexion)).c_str()))
			{
				ShowDataGP(GpInput[i]);
			}
		}
	}
}

void Engine::Input::ShowDataGP(const GamepadInput& GpInput)
{
	if (Wrapper::GUI::TreeNode("Axis##" + std::to_string(GpInput.IDconnexion), false))
	{
		Wrapper::GUI::DisplayFloat("Left stick X axis ", GpInput.axis[GLFW_GAMEPAD_AXIS_LEFT_X]);
		Wrapper::GUI::DisplayFloat("Left stick Y axis ", GpInput.axis[GLFW_GAMEPAD_AXIS_LEFT_Y]);
		Wrapper::GUI::DisplayFloat("Right stick X axis ", GpInput.axis[GLFW_GAMEPAD_AXIS_RIGHT_X]);
		Wrapper::GUI::DisplayFloat("Right stick Y axis ", GpInput.axis[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
		Wrapper::GUI::DisplayFloat("Left trigger axis ", GpInput.axis[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER]);
		Wrapper::GUI::DisplayFloat("Right trigger axis ", GpInput.axis[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER]);
		Wrapper::GUI::TreePop();
	}

	if (Wrapper::GUI::TreeNode("Button##" + std::to_string(GpInput.IDconnexion), false))
	{
		Wrapper::GUI::DisplayText("Button A : %d", GpInput.button[GamepadButton::BUTTON_A]);
		Wrapper::GUI::DisplayText("Button B : %d", GpInput.button[GamepadButton::BUTTON_B]);
		Wrapper::GUI::DisplayText("Button X : %d", GpInput.button[GamepadButton::BUTTON_X]);
		Wrapper::GUI::DisplayText("Button Y : %d", GpInput.button[GamepadButton::BUTTON_Y]);
		Wrapper::GUI::DisplayText("Left Bumper : %d", GpInput.button[GamepadButton::BUTTON_LEFT_BUMPER]);
		Wrapper::GUI::DisplayText("Right Bumper : %d", GpInput.button[GamepadButton::BUTTON_RIGHT_BUMPER]);
		Wrapper::GUI::DisplayText("Back : %d", GpInput.button[GamepadButton::BUTTON_BACK]);
		Wrapper::GUI::DisplayText("Start : %d", GpInput.button[GamepadButton::BUTTON_START]);
		Wrapper::GUI::DisplayText("Guide : %d", GpInput.button[14]);
		Wrapper::GUI::DisplayText("Left Thumb : %d", GpInput.button[GamepadButton::BUTTON_LEFT_THUMB]);
		Wrapper::GUI::DisplayText("Right Thumb : %d", GpInput.button[GamepadButton::BUTTON_RIGHT_THUMB]);
		Wrapper::GUI::DisplayText("Pad Up : %d", GpInput.button[GamepadButton::BUTTON_DPAD_UP]);
		Wrapper::GUI::DisplayText("Pad Right : %d", GpInput.button[GamepadButton::BUTTON_DPAD_RIGHT]);
		Wrapper::GUI::DisplayText("Pad Down : %d", GpInput.button[GamepadButton::BUTTON_DPAD_DOWN]);
		Wrapper::GUI::DisplayText("Pad Left : %d", GpInput.button[GamepadButton::BUTTON_DPAD_LEFT]);
		Wrapper::GUI::TreePop();
	}
}	


