#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Maths/Maths.hpp"

#include "dllInclude.hpp"

namespace Engine
{
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

		void Init(GLFWwindow* _window);
		
		void ScrollBackDoor(int value);

		float GetHorizontalAxis();
		float GetVerticalAxis();

		bool IsKeyPressed(int key);
		bool IsKeyDown(int key);
		bool IsKeyReleased(int key);
		bool IsAnyKeyDown();



		bool IsMouseButtonPressed(int mouseButton);
		bool IsMouseButtonDown(int mouseButton);
		bool IsMouseButtonUp(int mouseButton);
		bool IsMouseButtonReleased(int mouseButton);

		Maths::Vec2 GetMouseDelta();
		int GetScrollDelta();
		Maths::Vec2 GetMousePos() { return mousePosition; }

		static float deltaTime;
	private:
		Input() {}

		GLFWwindow* window;
		Maths::Vec2 mousePosition;
		Maths::Vec2 mouseDelta;
		int scrollDelta;

		int keyMap[348] = {0};
		int mouseMap[3] = {0};
		float timeStep ;
		bool anyKeyDown = false;

		void DisplayGUI();

	};
}

