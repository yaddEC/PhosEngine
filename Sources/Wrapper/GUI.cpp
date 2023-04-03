// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------


#include "imgui.h"
#include "imgui_internal.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Resource/Texture.hpp"

#include "LowRenderer/Framebuffer.hpp"

#define GUI_EXPORTS
#include "Wrapper/GUI.hpp"

bool Wrapper::GUI::InitGUI(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	// Set up ImGui
	ImGuiIO& io = ImGui::GetIO();

	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	return true;
}

void Wrapper::GUI::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Wrapper::GUI::RenderFrame(GLFWwindow* window)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0, 0.2f, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	ImGui::EndFrame();
}

void Wrapper::GUI::DestroyGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}


bool Wrapper::GUI::BeginWindow(const std::string& name, bool canCollpase)
{
	ImGuiWindowFlags Flag = ImGuiWindowFlags_None;
	if (!canCollpase)
		Flag |= ImGuiWindowFlags_NoCollapse;
	return ImGui::Begin(name.c_str(), 0, Flag);
}

void Wrapper::GUI::EndWindow()
{
	ImGui::End();
}

void Wrapper::GUI::BeginGroup()
{
	ImGui::BeginGroup();
}
void Wrapper::GUI::BeginGroupCentered(Maths::Vec2 sizeOfGroup)
{
	Maths::Vec2 r = (Maths::Vec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y) - sizeOfGroup) * 0.5f;
	ImGui::SetCursorPos(ImVec2(r.x, r.y));
	ImGui::BeginGroup();
}

void Wrapper::GUI::EndGroup()
{
	ImGui::EndGroup();
}

void Wrapper::GUI::DockingSpace()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::DockSpaceOverViewport(viewport);
}

Maths::Vec2 Wrapper::GUI::GetWindowSize()
{
	return Maths::Vec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
}

bool Wrapper::GUI::IsWondowFocused()
{
	return ImGui::IsWindowFocused();
}

Maths::Vec2 Wrapper::GUI::GetCursorPos()
{
	ImVec2 pos = ImGui::GetCursorPos();
	return Maths::Vec2(pos.x, pos.y);
}

void Wrapper::GUI::SetCursorPos(const Maths::Vec2& pos)
{
	ImGui::SetCursorPos(ImVec2{ pos.x, pos.y });
}

void Wrapper::GUI::Separator()
{
	ImGui::Separator();
}

void Wrapper::GUI::SameLine(float spacing)
{
	ImGui::SameLine(0, spacing);
}

void Wrapper::GUI::Image(const Resource::Texture& texture, Maths::Vec2 size)
{
	ImGui::Image((ImTextureID)texture.GetTextureKey(), ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
}

Maths::Vec2 Wrapper::GUI::CalcTextSize(const std::string& text)
{
	ImVec2 size = ImGui::CalcTextSize(text.c_str());
	return Maths::Vec2(size.x, size.y);
}

bool Wrapper::GUI::TruncTextBySize(std::string& text, float maxLength)
{
	bool trunced = false;
	while (CalcTextSize(text).x > maxLength)
	{
		text.pop_back();
		trunced = true;
	}
	return trunced;
}

bool Wrapper::GUI::EditFloat(const std::string& label, float& value, float speed, float min, float max)
{
	return ImGui::DragFloat(label.c_str(), &value, speed, min, max);
}

bool Wrapper::GUI::EditVec2(const std::string& label, Maths::Vec2& value, float speed, float min, float max)
{
	return ImGui::DragFloat2(label.c_str(), &value.x, speed, min, max);
}

bool Wrapper::GUI::EditVec3(const std::string& label, Maths::Vec3& value, float speed, float min, float max)
{
	return ImGui::DragFloat3(label.c_str(), &value.x, speed, min, max);
}

bool Wrapper::GUI::EditColorRGB(const std::string& label, Maths::Vec3& value)
{
	return ImGui::ColorEdit3(label.c_str(), &value.x);
}

bool Wrapper::GUI::EditColorRGBA(const std::string& label, Maths::Vec4& value)
{
	return ImGui::ColorEdit4(label.c_str(), &value.x);
}

void Wrapper::GUI::DisplayText(const std::string& text)
{
	ImGui::Text(text.c_str());
}

void Wrapper::GUI::DisplayFloat(const std::string& label, float value)
{
	return ImGui::Text((label + " : " + std::to_string(value)).c_str());
}

void Wrapper::GUI::DisplayVec2(const std::string& label, const Maths::Vec2& value)
{
	return ImGui::Text((label + " : (" + std::to_string(value.x) + ", " + std::to_string(value.y) + ")").c_str());
}

void Wrapper::GUI::DisplayVec3(const std::string& label, const Maths::Vec3& value)
{
	return ImGui::Text((label + " : (" + std::to_string(value.x) + ", " + std::to_string(value.y) + ", " + std::to_string(value.z) + ")").c_str());
}

bool Wrapper::GUI::Button(const std::string& label, const Maths::Vec2& size)
{
	return ImGui::Button(label.c_str(), ImVec2(size.x, size.y));
}

bool Wrapper::GUI::CheckBox(const std::string& label, bool* isChecked)
{
	return ImGui::Checkbox(label.c_str(), isChecked);
}

bool Wrapper::GUI::Selectable(const std::string& label, bool isSelected, const Maths::Vec2& size)
{
	return ImGui::Selectable(label.c_str(), &isSelected, 0, ImVec2(size.x, size.y));
}

bool Wrapper::GUI::Combo(const std::string& label, const std::vector<std::string>& list, std::string& selected)
{
	if (ImGui::BeginCombo(label.c_str(), selected.c_str()))
	{
		for (auto str : list)
		{
			if (ImGui::Selectable(str.c_str(), str == selected))
			{
				selected = str;
				ImGui::EndCombo();
				return true;
			}
		}
		ImGui::EndCombo();
		return false;
	}
}

bool Wrapper::GUI::TreeNode(const std::string& label, bool isSelected, bool leaf)
{
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
	if (isSelected)
		nodeFlags |= ImGuiTreeNodeFlags_Selected;
	if (leaf)
		nodeFlags |= ImGuiTreeNodeFlags_Leaf;

	return ImGui::TreeNodeEx(label.c_str(), nodeFlags);
}

void Wrapper::GUI::TreePop()
{
	ImGui::TreePop();
}

bool Wrapper::GUI::CollapsingHeader(const std::string& label)
{
	return ImGui::CollapsingHeader(label.c_str());
}

bool Wrapper::GUI::IsItemClicked(int mouseButton)
{
	return ImGui::IsItemClicked(mouseButton);
}

bool Wrapper::GUI::IsItemDoubleClicked(int mouseButton)
{	
	return ImGui::IsMouseDoubleClicked(mouseButton) && ImGui::IsItemHovered();
}

void Wrapper::GUI::DragDropSource(const std::string& ID, const std::string& label, const void* data)
{
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
	{
		ImGui::SetDragDropPayload(ID.c_str(), data, sizeof(data));
		ImGui::Text(label.c_str());
		ImGui::EndDragDropSource();
	}
}

void* Wrapper::GUI::DragDropTarget(const std::string& ID)
{
	void* result = nullptr;
	if (ImGui::BeginDragDropTarget())
	{
		// Enable dropping textures onto materials.
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(ID.c_str(), ImGuiDragDropFlags_SourceAllowNullID))
		{
			result = payload->Data;
		}
		ImGui::EndDragDropTarget();
	}
	return result;
}


bool Wrapper::GUI::BeginPopupContextItem(const std::string& ID)
{
	return ImGui::BeginPopupContextItem(ID.c_str());
}

void Wrapper::GUI::EndPopup()
{
	ImGui::EndPopup();
}

void Wrapper::GUI::OpenPopup(const std::string& ID)
{
	ImGui::OpenPopup(ID.c_str());
}

void Wrapper::GUI::Demo()
{
	ImGui::ShowDemoWindow();
}

void Wrapper::GUI::MenuBar(void(*funcTopBar)(void), void(*funcBottomBar)(void))
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBackground;
	float height = ImGui::GetFrameHeight();

	if (ImGui::BeginViewportSideBar("##MainStatusBar", NULL, ImGuiDir_Up, height, window_flags)) {
		if (ImGui::BeginMenuBar()) {
			funcTopBar();
			ImGui::EndMenuBar();
		}
	}
	ImGui::End();
	if (ImGui::BeginViewportSideBar("##SecondaryMenuBar", NULL, ImGuiDir_Up, height, window_flags)) {
		if (ImGui::BeginMenuBar()) {
			funcBottomBar();
			ImGui::EndMenuBar();
		}
	}
	ImGui::End();
}

bool Wrapper::GUI::BeginMenu(const char* name)
{
	return ImGui::BeginMenu(name);
}
void Wrapper::GUI::EndMenu()
{
	ImGui::EndMenu();
}
bool Wrapper::GUI::MenuItem(const char* label, const char* shortcut, bool selected)
{
	return ImGui::MenuItem(label, shortcut, selected);
}
bool Wrapper::GUI::MenuItem(const char* label, const char* shortcut)
{
	return ImGui::MenuItem(label, shortcut);
}

void Wrapper::GUI::PushFontSize(float size)
{
	ImFont* font = ImGui::GetFont();
	font->FontSize = size;
	ImGui::PushFont(font);
}

void Wrapper::GUI::PopFontSize()
{
	ImGui::PopFont();
}

void Wrapper::GUI::SetWindowFontSize(float size)
{
	ImGui::SetWindowFontScale(size);
}
