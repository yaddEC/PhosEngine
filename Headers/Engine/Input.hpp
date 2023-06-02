#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Maths/Maths.hpp"
#include <map>
#include <string>

namespace Engine
{
	constexpr int MAX_CONTROLLER = 4;
	constexpr int MOUSE_DELTA_X = -1;
	constexpr int MOUSE_DELTA_Y = -2;
	constexpr const char* ControllerName[6] {"None", "Keyboard", "Gamepad 1", "Gamepad 2" , "Gamepad 3" , "Gamepad 4" };

	enum class Controller : int
	{
		C_NONE = -2,
		C_KEYBOARD,
		C_GAMEPAD_1,
		C_GAMEPAD_2,
		C_GAMEPAD_3,
		C_GAMEPAD_4
	};

	
	
	enum GamepadButton
	{
		BUTTON_A = GLFW_GAMEPAD_BUTTON_A,
		BUTTON_B = GLFW_GAMEPAD_BUTTON_B,               
		BUTTON_X = GLFW_GAMEPAD_BUTTON_X,               
		BUTTON_Y = GLFW_GAMEPAD_BUTTON_Y,               
		BUTTON_LEFT_BUMPER = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
		BUTTON_RIGHT_BUMPER = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
		BUTTON_BACK = GLFW_GAMEPAD_BUTTON_BACK,
		BUTTON_START = GLFW_GAMEPAD_BUTTON_START,
		BUTTON_LEFT_THUMB = GLFW_GAMEPAD_BUTTON_GUIDE,
		BUTTON_RIGHT_THUMB = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
		BUTTON_DPAD_UP = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
		BUTTON_DPAD_RIGHT = GLFW_GAMEPAD_BUTTON_DPAD_UP,
		BUTTON_DPAD_DOWN = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
		BUTTON_DPAD_LEFT = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
	};

	enum GamepadAxis
	{
		AXIS_LEFT_STICK_X = GLFW_GAMEPAD_AXIS_LEFT_X,
		AXIS_LEFT_STICK_Y = GLFW_GAMEPAD_AXIS_LEFT_Y,
		AXIS_RIGHT_STICK_X = GLFW_GAMEPAD_AXIS_RIGHT_X,
		AXIS_RIGHT_STICK_Y = GLFW_GAMEPAD_AXIS_RIGHT_Y,
		AXIS_LEFT_TRIGGER = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
		AXIS_RIGHT_TRIGGER = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER
	};

	struct GamepadInput
	{
		// -1 is disconnect
		int IDconnexion = -1;

		float axis[6] = { 0 };
		int button[15] = { 0 };
	};

	struct ActionAxis
	{
		ActionAxis(int _keyboardPos, int _keyboardNeg, GamepadAxis _axis)
			: keyboardPos(_keyboardPos), keyboardNeg(_keyboardNeg), gamepadAxis(_axis), mouse(false) {}

		ActionAxis(int _mouseAxis, GamepadAxis _axis)
			: mouseAxis(_mouseAxis), gamepadAxis(_axis), mouse(true) {}

		int keyboardPos, keyboardNeg;
		int mouseAxis;
		bool mouse;
		GamepadAxis gamepadAxis;
	};

	class PHOSENGINE_API Input
	{
	public:

		Input(const Input&) = delete;

		static Input& GetInstance()
		{
			static Input instance;
			return instance;
		}

		void Update();
		void UpdateGamePad();

		void Init(GLFWwindow* _window);
		
		void ScrollBackDoor(int value);

		float GetHorizontalAxis();
		float GetVerticalAxis();

		float GetGamepadAxis(int axis, int idPlayer);

		GamepadInput* GetGamepad() { return GpInput; }

		// Keyboard Input
		bool IsKeyPressed(int key);
		bool IsKeyDown(int key);
		bool IsKeyReleased(int key);
		bool IsAnyKeyDown();

		// Gamepad Input
		bool IsButtonPressed(int key, int idPlayer);
		bool IsButtonDown(int key, int idPlayer);
		bool IsButtonReleased(int key, int idPlayer);

		// Mouse Input
		bool IsMouseButtonPressed(int mouseButton);
		bool IsMouseButtonDown(int mouseButton);
		bool IsMouseButtonUp(int mouseButton);
		bool IsMouseButtonReleased(int mouseButton);
		Maths::Vec2 GetMouseDelta();
		int GetScrollDelta();
		Maths::Vec2 GetMousePos() { return mousePosition; }

		void DisplayGUI();
		void ShowDataGP(const GamepadInput& GpInput);

		float GetDeltaTime() { return deltaTime; }

		float GetAxis(const char* axis, Controller controller);

	private:
		Input() {}

		GLFWwindow* window;
		Maths::Vec2 mousePosition;
		Maths::Vec2 mouseDelta;
		int scrollDelta;

		GamepadInput GpInput[MAX_CONTROLLER] = { 0 };

		int keyMap[348] = {0};
		int mouseMap[3] = {0};
		float timeStep ;
		bool anyKeyDown = false;

		float deltaTime;

		void InitAxisMap();
		std::map<std::string, ActionAxis> m_AxisMap;

	};
}

