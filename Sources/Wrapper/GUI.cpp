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

bool GUI::InitGUI(GLFWwindow* window)
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

void GUI::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUI::RenderFrame(GLFWwindow* window)
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

void GUI::DestroyGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}


bool GUI::BeginWindow(const std::string& name, bool canCollpase)
{
	ImGuiWindowFlags Flag = ImGuiWindowFlags_None;
	if (!canCollpase)
		Flag |= ImGuiWindowFlags_NoCollapse;
	return ImGui::Begin(name.c_str(), 0, Flag);
}

void GUI::EndWindow()
{
	ImGui::End();
}

void GUI::BeginGroup()
{
	ImGui::BeginGroup();
}
void GUI::BeginGroupCentered(Maths::Vec2 sizeOfGroup)
{
	Maths::Vec2 r = (Maths::Vec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y) - sizeOfGroup) * 0.5f;
	ImGui::SetCursorPos(ImVec2(r.x, r.y));
	ImGui::BeginGroup();
}

void GUI::EndGroup()
{
	ImGui::EndGroup();
}

void GUI::DockingSpace()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::DockSpaceOverViewport(viewport);
}

Maths::Vec2 GUI::GetWindowSize()
{
	return Maths::Vec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
}

bool GUI::IsWondowFocused()
{
	return ImGui::IsWindowFocused();
}

Maths::Vec2 GUI::GetCursorPos()
{
	ImVec2 pos = ImGui::GetCursorPos();
	return Maths::Vec2(pos.x, pos.y);
}

void GUI::SetCursorPos(const Maths::Vec2& pos)
{
	ImGui::SetCursorPos(ImVec2{ pos.x, pos.y });
}

void GUI::Separator()
{
	ImGui::Separator();
}

void GUI::SameLine(float spacing)
{
	ImGui::SameLine(0, spacing);
}

void GUI::Image(const Resource::Texture& texture, Maths::Vec2 size)
{
	ImGui::Image((ImTextureID)texture.GetTextureKey(), ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
}

bool GUI::EditFloat(const std::string& label, float& value, float speed, float min, float max)
{
	return ImGui::DragFloat(label.c_str(), &value, speed, min, max);
}

bool GUI::EditVec2(const std::string& label, Maths::Vec2& value, float speed, float min, float max)
{
	return ImGui::DragFloat2(label.c_str(), &value.x, speed, min, max);
}

bool GUI::EditVec3(const std::string& label, Maths::Vec3& value, float speed, float min, float max)
{
	return ImGui::DragFloat3(label.c_str(), &value.x, speed, min, max);
}

bool GUI::EditColorRGB(const std::string& label, Maths::Vec3& value)
{
	return ImGui::ColorEdit3(label.c_str(), &value.x);
}

bool GUI::EditColorRGBA(const std::string& label, Maths::Vec4& value)
{
	return ImGui::ColorEdit4(label.c_str(), &value.x);
}

void GUI::DisplayText(const std::string& text)
{
	ImGui::Text(text.c_str());
}

void GUI::DisplayFloat(const std::string& label, float value)
{
	return ImGui::Text((label + " : " + std::to_string(value)).c_str());
}

void GUI::DisplayVec2(const std::string& label, const Maths::Vec2& value)
{
	return ImGui::Text((label + " : (" + std::to_string(value.x) + ", " + std::to_string(value.y) + ")").c_str());
}

void GUI::DisplayVec3(const std::string& label, const Maths::Vec3& value)
{
	return ImGui::Text((label + " : (" + std::to_string(value.x) + ", " + std::to_string(value.y) + ", " + std::to_string(value.z) + ")").c_str());
}

bool GUI::Button(const std::string& label, const Maths::Vec2& size)
{
	return ImGui::Button(label.c_str(), ImVec2(size.x, size.y));
}

bool GUI::Selectable(const std::string& label, const Maths::Vec2& size)
{
	return ImGui::Selectable(label.c_str(), nullptr, 0, ImVec2(size.x, size.y));
}

bool GUI::TreeNode(const std::string& label, bool isSelected, bool leaf)
{
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
	if (isSelected)
		nodeFlags |= ImGuiTreeNodeFlags_Selected;
	if (leaf)
		nodeFlags |= ImGuiTreeNodeFlags_Leaf;

	return ImGui::TreeNodeEx(label.c_str(), nodeFlags);
}

void GUI::TreePop()
{
	ImGui::TreePop();
}

bool GUI::CollapsingHeader(const std::string& label)
{
	return ImGui::CollapsingHeader(label.c_str());
}

bool GUI::IsItemClicked(int mouseButton)
{
	return ImGui::IsItemClicked(mouseButton);
}

void GUI::DragDropSource(const std::string& ID, const std::string& label, const void* data)
{
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
	{
		ImGui::SetDragDropPayload(ID.c_str(), data, sizeof(data));
		ImGui::Text(label.c_str());
		ImGui::EndDragDropSource();
	}
}

void* GUI::DragDropTarget(const std::string& ID)
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


bool GUI::BeginPopupContextItem(const std::string& ID)
{
	return ImGui::BeginPopupContextItem(ID.c_str());
}

void GUI::EndPopup()
{
	ImGui::EndPopup();
}

void GUI::OpenPopup(const std::string& ID)
{
	ImGui::OpenPopup(ID.c_str());
}

void GUI::Demo()
{
	ImGui::ShowDemoWindow();
}

void GUI::MenuBar(void(*funcTopBar)(void), void(*funcBottomBar)(void))
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

bool GUI::BeginMenu(const char* name)
{
	return ImGui::BeginMenu(name);
}
void GUI::EndMenu()
{
	ImGui::EndMenu();
}
bool GUI::MenuItem(const char* label, const char* shortcut, bool selected)
{
	return ImGui::MenuItem(label, shortcut, selected);
}
bool GUI::MenuItem(const char* label, const char* shortcut)
{
	return ImGui::MenuItem(label, shortcut);
}