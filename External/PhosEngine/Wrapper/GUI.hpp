#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Maths/Maths.hpp"

#ifdef GUI_EXPORTS
#define GUI_API __declspec(dllexport)
#else
#define GUI_API __declspec(dllimport)
#endif

namespace Resource
{
	class Texture;
}

class GUI_API GUI
{
public:
	static bool InitGUI(GLFWwindow* window);
	static void NewFrame();
	static void RenderFrame(GLFWwindow* window);
	static void DestroyGUI(); // Has to be called at the end of the application.
	 
	static bool BeginWindow(const std::string& name, bool canCollpase = false);
	static void EndWindow();
	 
	static void DockingSpace();
	 
	static Maths::Vec2 GetWindowSize();
	static bool IsWondowFocused();
	 
	static void Image(const Resource::Texture& texture, Maths::Vec2 size);
	 
	static bool EditFloat(const std::string& label, float& value, float speed = 1.f, float min = 0, float max = 0);
	static bool EditVec2(const std::string& label, Maths::Vec2& value, float speed = 1.f, float min = 0, float max = 0);
	static bool EditVec3(const std::string& label, Maths::Vec3& value, float speed = 1.f, float min = 0, float max = 0);
	static bool EditColorRGB(const std::string& label, Maths::Vec3& value);
	static bool EditColorRGBA(const std::string& label, Maths::Vec4& value);
	 
	static void DisplayText(const std::string& text);
	static void DisplayFloat(const std::string& label, float value);
	static void DisplayVec2(const std::string& label, const Maths::Vec2& value);
	static void DisplayVec3(const std::string& label, const Maths::Vec3& value);

};
