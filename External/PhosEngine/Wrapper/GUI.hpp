#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
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

namespace Wrapper
{
	class GUI_API GUI
	{
	public:
		static bool InitGUI(GLFWwindow* window);
		static void NewFrame();
		static void RenderFrame(GLFWwindow* window);
		static void DestroyGUI(); // Has to be called at the end of the application.

		static void DockingSpace();

		static bool BeginWindow(const std::string& name, bool canCollpase = false);
		static void EndWindow();

		static void BeginGroup();
		static void BeginGroupCentered(Maths::Vec2 sizeOfGroup);
		static void EndGroup();

		static bool BeginPopupContextItem(const std::string& ID);
		static void EndPopup();
		static void OpenPopup(const std::string& ID);

		static bool TreeNode(const std::string& label, bool isSelected, bool leaf = false);
		static void TreePop();

		static bool CollapsingHeader(const std::string& label);

		static Maths::Vec2 GetWindowSize();
		static bool IsWondowFocused();

		static Maths::Vec2 GetCursorPos();
		static void SetCursorPos(const Maths::Vec2& pos);

		static void Separator();
		static void SameLine(float spacing = -1.f);

		static void Image(const Resource::Texture& texture, Maths::Vec2 size);

		static Maths::Vec2 CalcTextSize(const std::string& text);
		static bool TruncTextBySize(std::string& text, float maxLength);

		static bool EditFloat(const std::string& label, float& value, float speed = 1.f, float min = 0, float max = 0);
		static bool EditVec2(const std::string& label, Maths::Vec2& value, float speed = 1.f, float min = 0, float max = 0);
		static bool EditVec3(const std::string& label, Maths::Vec3& value, float speed = 1.f, float min = 0, float max = 0);
		static bool EditColorRGB(const std::string& label, Maths::Vec3& value);
		static bool EditColorRGBA(const std::string& label, Maths::Vec4& value);

		static void DisplayText(const std::string& text);
		static void DisplayFloat(const std::string& label, float value);
		static void DisplayVec2(const std::string& label, const Maths::Vec2& value);
		static void DisplayVec3(const std::string& label, const Maths::Vec3& value);

		static bool Button(const std::string& label, const Maths::Vec2& size = Maths::Vec2(0, 0));
		static bool CheckBox(const std::string& label, bool* isChecked);
		static bool Selectable(const std::string& label, bool isSelected, const Maths::Vec2& size = Maths::Vec2(0, 0));
		static bool Combo(const std::string& label, const std::vector<std::string>& list, std::string& selected);

		static bool IsItemClicked(int mouseButton);
		static bool IsItemDoubleClicked(int mouseButton);

		static void DragDropSource(const std::string& ID, const std::string& Label, const void* data);
		static void* DragDropTarget(const std::string& ID);

		static void Demo();
		static void MenuBar(void(*funcTopBar)(void), void(*funcBottomBar)(void));

		static bool BeginMenu(const char* name);
		static void EndMenu();

		static bool MenuItem(const char* label, const char* shortcut, bool selected);
		static bool MenuItem(const char* label, const char* shortcut);

		static void PushFontSize(float size);
		static void PopFontSize();
		static void SetWindowFontSize(float size);

	};
}