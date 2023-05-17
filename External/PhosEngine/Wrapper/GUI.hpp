#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <functional>

#include "Maths/Maths.hpp"
#include "Engine/Input.hpp"

#include "dllInclude.hpp"

namespace Resource
{
	class Texture; 
	class Mesh; 
	class Material;
	class PostProcessingShader;
}

namespace Wrapper
{
	class Window;

	class PHOSENGINE_API GUI
	{
	public:
		static bool InitGUI(GLFWwindow* window);
		static void NewFrame();
		static void RenderFrame(GLFWwindow* window);
		static void DestroyGUI(); // Has to be called at the end of the application.

		static void DockingSpace();

		static bool BeginWindow(const std::string& name, bool canCollpase = false, bool isDialogBox = false, bool canBeClosed = false, bool* isOpen = nullptr);
		static void EndWindow();

		static void BeginGroup();
		static void BeginGroupCentered(Maths::Vec2 sizeOfGroup);
		static void EndGroup();

		static bool BeginPopup(const std::string& ID, bool isNormalPopUp = true);
		static bool BeginPopupContextItem(const std::string& ID);
		static bool BeginPopupModal(const std::string& ID);
		static void EndPopup();
		static void CloseCurrentPopUp();
		static void OpenPopup(const std::string& ID);

		static bool TreeNode(const std::string& label, bool isSelected, bool leaf = false);
		static void TreePop();

		static bool CollapsingHeader(const std::string& label);

		static void PushID(int ID);
		static void PopID();

		static Maths::Vec2 GetWindowSize();
		static Maths::Vec2 GetWindowPos(const Wrapper::Window& window);
		static bool IsWondowFocused();
		static bool IsWindowHovered();

		static Maths::Vec2 GetCursorPos();
		static void SetCursorPos(const Maths::Vec2& pos);

		static void Separator();
		static void SameLine(float spacing = -1.f);
		static void SetNextItemWidth(float item_width);
		static void SetKeyboardFocusHere();

		static void Image(const Resource::Texture& texture, Maths::Vec2 size);

		static void TextUnformatted(const std::string& text, const std::string& text_end = "");
		static Maths::Vec2 CalcTextSize(const std::string& text);
		static bool TruncTextBySize(std::string& text, float maxLength);

		static bool SliderFloat(const std::string& label, float& value, bool text = true, float min = 0, float max = 0);
		static bool EditFloat(const std::string& label, float& value, bool text = true, float speed = 1.f, float min = 0, float max = 0);
		static bool EditVec2(const std::string& label, Maths::Vec2& value, bool text = true, float speed = 1.f, float min = 0, float max = 0);
		static bool EditVec3(const std::string& label, Maths::Vec3& value, bool text = true, float speed = 1.f, float min = 0, float max = 0);
		static bool EditColorRGB(const std::string& label, Maths::Vec3& value, bool text = true);
		static bool EditColorRGBA(const std::string& label, Maths::Vec4& value, bool text = true);

		static bool EditFloat(const std::string& label, float* value, bool text = true, float speed = 1.f, float min = 0, float max = 0);
		static bool EditVec2(const std::string& label, Maths::Vec2* value, bool text = true, float speed = 1.f, float min = 0, float max = 0);
		static bool EditVec3(const std::string& label, Maths::Vec3* value, bool text = true, float speed = 1.f, float min = 0, float max = 0);
		static bool EditColorRGB(const std::string& label, Maths::Vec3* value, bool text = true);
		static bool EditColorRGBA(const std::string& label, Maths::Vec4* value, bool text = true);

		static bool PickTexture(const std::string& label, Resource::Texture** texture, bool text = true);
		static bool PickMesh(const std::string& label, Resource::Mesh** mesh, bool text = true);
		static bool PickMaterial(const std::string& label, Resource::Material** material, bool text = true);
		static bool PickPostProcessing(const std::string& label, Resource::PostProcessingShader** material, bool text = true);

		static void DisplayText(const char* format,...);
		static void DisplayFloat(const std::string& label, float value);
		static void DisplayVec2(const std::string& label, const Maths::Vec2& value);
		static void DisplayVec3(const std::string& label, const Maths::Vec3& value);

		static bool InputString(const std::string& label, std::string& value);
		static bool Button(const std::string& label, const Maths::Vec2& size = Maths::Vec2(0, 0));
		static bool CheckBox(const std::string& label, bool* isChecked);
		static bool Selectable(const std::string& label, bool isSelected, const Maths::Vec2& size = Maths::Vec2(0, 0));
		static bool Combo(const std::string& label, const std::vector<std::string>& list, std::string& selected, bool text = false, const std::string& first = "");

		static bool IsItemHovered();
		static bool IsItemDown(int mouseButton);
		static bool IsItemClicked(int mouseButton);
		static bool IsItemDoubleClicked(int mouseButton);

		static void DragDropSource(const std::string& ID, const std::string& Label, const void* data);
		static void* DragDropTarget(const std::string& ID);

		static void Demo();
		static void MenuBar(std::function<void()> funcTopBar);

		static bool BeginMenu(const char* name);
		static void EndMenu();

		static bool BeginMenuBar();
		static void EndMenuBar();

		static bool MenuItem(const char* label, const char* shortcut, bool selected);
		static bool MenuItem(const char* label, const char* shortcut);

		static void PushFontSize(float size);
		static void PopFontSize();
		static void SetWindowFontSize(float size);

	};
}