
// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <cstdint> 

#include "imgui.h"
#include "imgui_internal.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdarg>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Resource/ResourceIncludes.hpp"
#include "Resource/ResourceManager.hpp"
#include "Wrapper/Window.hpp"
#include "LowRenderer/Framebuffer.hpp"

#include "ImGuizmo/Header/ImGuizmo.h"

#include "Wrapper/GUI.hpp"


bool Wrapper::GUI::InitGUI(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//Set up Style 
	ImGui::StyleColorsDark();

	auto& Style = ImGui::GetStyle();

	Style.WindowRounding = 7.000f;
	Style.WindowBorderSize = 0.000f;
	Style.ChildRounding = 7.000f;
	Style.ChildBorderSize = 0.000f;
	Style.PopupRounding = 7.000f;
	Style.PopupBorderSize = 1.000f;
	Style.FrameRounding = 7.000f;
	Style.ScrollbarSize = 15.000f;
	Style.ScrollbarRounding = 7.000f;
	Style.GrabMinSize = 9.000f;
	Style.GrabRounding = 7.000f;
	Style.LogSliderDeadzone = 7.000f;
	Style.TabRounding = 7.000f;
	Style.WindowMenuButtonPosition = ImGuiDir_None;
	

	Style.Colors[ImGuiCol_FrameBg] = ImVec4(0.305f, 0.310f, 0.316f, 0.540f);
	Style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);
	Style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);
	Style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.122f, 0.361f, 0.357f, 1.000f);
	Style.Colors[ImGuiCol_CheckMark] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);
	Style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.180f, 0.659f, 0.631f, 1.000f);
	Style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);
	Style.Colors[ImGuiCol_Button] = ImVec4(0.196f, 0.737f, 0.702f, 0.749f);
	Style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.196f, 0.737f, 0.702f, 0.835f);
	Style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.047f, 0.737f, 0.647f, 0.753f);
	Style.Colors[ImGuiCol_Header] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);
	Style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);
	Style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);
	Style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);
	Style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);
	Style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);
	Style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.238f, 0.918f, 0.873f, 1.000f);
	Style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.196f, 0.737f, 0.702f, 0.758f);
	Style.Colors[ImGuiCol_Tab] = ImVec4(0.137f, 0.435f, 0.424f, 1.000f);
	Style.Colors[ImGuiCol_TabHovered] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);
	Style.Colors[ImGuiCol_TabActive] = ImVec4(0.153f, 0.510f, 0.486f, 1.000f);
	Style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.051f, 0.110f, 0.110f, 1.000f);
	Style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.102f, 0.318f, 0.306f, 1.000f);
	Style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.749f, 0.263f, 0.502f, 1.000f);
	Style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.678f, 0.114f, 0.004f, 1.000f);
	Style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.749f, 0.004f, 0.020f, 1.000f);
	Style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);
	Style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.749f, 0.282f, 0.004f, 1.000f);
	Style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.196f, 0.737f, 0.702f, 1.000f);

	static const ImWchar ranges1[] =
	{
	0x25A0,0x25A0,
	0x258D,0x258D,
	0x2009,0x2009,
	};
	static const ImWchar ranges2[] =
	{
	0x25BA,0x25BA,
	
	};
	// Set up ImGui
	ImGuiIO& io = ImGui::GetIO();

	io.Fonts->AddFontFromFileTTF("DefaultAssets/Font/Figtree-Regular.ttf", 18.000f,0);
	ImFontConfig config;
	config.GlyphRanges = ranges2;
	config.MergeMode = true;
	io.Fonts->AddFontFromFileTTF("DefaultAssets/Font/Arial.ttf", 18.000f,&config, ranges2);
	config.GlyphRanges = ranges1;
	io.Fonts->AddFontFromFileTTF("DefaultAssets/Font/seguisym.ttf", 18.000f, &config, ranges1);
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


bool Wrapper::GUI::BeginWindow(const std::string& name, bool canCollpase, bool isDialogBox ,bool canBeClosed, bool* isOpen)
{
	ImGuiWindowClass windowClass;
	ImGuiWindowFlags Flag = ImGuiWindowFlags_None;
	if (!canCollpase)
		Flag |= ImGuiWindowFlags_NoCollapse;
	if (isDialogBox)
	{
		Flag |=  ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
		windowClass.DockNodeFlagsOverrideSet |= ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_NoDockingSplitMe | ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingOverOther;
	}
		ImGui::SetNextWindowClass(&windowClass);
	if(canBeClosed)
		return ImGui::Begin(name.c_str(), isOpen, Flag);
	else
		return ImGui::Begin(name.c_str(),(bool*)0, Flag);
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

Maths::Vec2 Wrapper::GUI::GetWindowPos(const Wrapper::Window& window)
{
	Maths::Vec2 pos = window.GetPos();
	return Maths::Vec2(pos.x - ImGui::GetWindowPos().x, pos.y - ImGui::GetWindowPos().y);
}

bool Wrapper::GUI::IsWondowFocused()
{
	return ImGui::IsWindowFocused();
}

bool Wrapper::GUI::IsWindowHovered()
{
	return ImGui::IsWindowHovered();
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

void Wrapper::GUI::SetNextItemWidth(float item_width)
{
	ImGui::SetNextItemWidth(item_width);
}

void Wrapper::GUI::SetKeyboardFocusHere()
{
	ImGui::SetKeyboardFocusHere();
}

void Wrapper::GUI::Image(const Resource::Texture& texture, Maths::Vec2 size)
{
	ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<uint64_t>(texture.GetTextureKey())), ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
}

void Wrapper::GUI::TextUnformatted(const std::string& text, const std::string& text_end)
{
	ImGui::TextUnformatted(text.c_str(),text_end.c_str());
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

bool Wrapper::GUI::SliderFloat(const std::string& label, float& value, bool text, float min, float max)
{
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine();
	}
	return ImGui::SliderFloat(("##" + label).c_str(), &value, min, max, "%.2f");
}

bool Wrapper::GUI::PickTexture(const std::string& label, Resource::Texture** texture, bool text)
{
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	std::vector<std::string> meshNameList = Resource::ResourceManager::GetInstance().GetResourceNameList<Resource::Texture>();
	std::string currentTextureName = *texture ? (*texture)->GetName() : "None";

	if (ImGui::BeginCombo(("##" + label).c_str(), currentTextureName.c_str()))
	{
		if (ImGui::Selectable("None", !texture))
		{
			*texture = nullptr;
			ImGui::EndCombo();
			return true;
		}

		for (auto str : meshNameList)
		{
			if (ImGui::Selectable(str.c_str(), str == currentTextureName))
			{
				*texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(str);
				ImGui::EndCombo();
				return true;
			}
		}
		ImGui::EndCombo();
	}
	if (Resource::Texture** newTexture = (Resource::Texture**)DragDropTarget("Texture"))
	{
		*texture = *newTexture;
		return true;
	}

	return false;
}


bool Wrapper::GUI::EditFloat(const std::string& label, float& value, bool text, float speed, float min, float max)
{
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	return ImGui::DragFloat(("##" + label).c_str(), &value, speed, min, max);
}

bool Wrapper::GUI::EditVec2(const std::string& label, Maths::Vec2& value, bool text, float speed, float min, float max)
{
	
	
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine(  WIDGET_OFFSET* GUI::GetWindowSize().x* GUI::GetWindowSize().x- textWidth);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x - textWidth);
	return ImGui::DragFloat2(("##" + label).c_str(), &value.x, speed, min, max);
}

bool Wrapper::GUI::EditVec3(const std::string& label, Maths::Vec3& value, bool text, float speed, float min, float max)
{
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	return ImGui::DragFloat3(("##" + label).c_str(), &value.x, speed, min, max);
}

bool Wrapper::GUI::EditColorRGB(const std::string& label, Maths::Vec3& value, bool text)
{
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	return ImGui::ColorEdit3(("##" + label).c_str(), &value.x);
}

bool Wrapper::GUI::EditColorRGBA(const std::string& label, Maths::Vec4& value, bool text)
{
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	return ImGui::ColorEdit4(("##" + label).c_str(), &value.x);
}

bool Wrapper::GUI::EditFloat(const std::string& label, float* value, bool text, float speed, float min, float max)
{
	 
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	return ImGui::DragFloat(("##" + label).c_str(), value, speed, min, max);
}

bool Wrapper::GUI::EditVec2(const std::string& label, Maths::Vec2* value, bool text, float speed, float min, float max)
{
	
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	return ImGui::DragFloat2(("##" + label).c_str(), &value->x, speed, min, max);
}

bool Wrapper::GUI::EditVec3(const std::string& label, Maths::Vec3* value, bool text, float speed, float min, float max)
{
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	return ImGui::DragFloat3(("##" + label).c_str(), &value->x, speed, min, max);
}

bool Wrapper::GUI::EditColorRGB(const std::string& label, Maths::Vec3* value, bool text)
{
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	return ImGui::ColorEdit3(("##" + label).c_str(), &value->x);
}

bool Wrapper::GUI::EditColorRGBA(const std::string& label, Maths::Vec4* value, bool text)
{
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	return ImGui::ColorEdit4(("##" + label).c_str(), &value->x);
}


bool Wrapper::GUI::PickMesh(const std::string& label, Resource::Mesh** mesh, bool text)
{

	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	std::vector<std::string> meshNameList = Resource::ResourceManager::GetInstance().GetResourceNameList<Resource::Mesh>();
	std::string currentMeshName = (*mesh) ? (*mesh)->GetName() : "None";

	if (ImGui::BeginCombo(("##" + label).c_str(), currentMeshName.c_str()))
	{
		if (ImGui::Selectable("None", !mesh))
		{
			*mesh = nullptr;
			ImGui::EndCombo();
			return true;
		}

		for (auto str : meshNameList)
		{
			if (ImGui::Selectable(str.c_str(), str == currentMeshName))
			{
				*mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(str);
				ImGui::EndCombo();
				return true;
			}
		}
		ImGui::EndCombo();
	}
	if (Resource::Mesh** newmesh = (Resource::Mesh**)DragDropTarget("Mesh"))
	{
		*mesh = *newmesh;
	}

	return false;
}

bool Wrapper::GUI::PickMaterial(const std::string& label, Resource::Material** material, bool text)
{
	
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	std::vector<std::string> meshNameList = Resource::ResourceManager::GetInstance().GetResourceNameList<Resource::Material>();
	std::string currentMeshName = (*material) ? (*material)->GetName() : "None";

	if (ImGui::BeginCombo(("##" + label).c_str(), currentMeshName.c_str()))
	{
		if (ImGui::Selectable("None", !material))
		{
			*material = nullptr;
			ImGui::EndCombo();
			return true;
		}

		for (auto str : meshNameList)
		{
			if (ImGui::Selectable(str.c_str(), str == currentMeshName))
			{
				*material = Resource::ResourceManager::GetInstance().GetResource<Resource::Material>(str);
				ImGui::EndCombo();
				return true;
			}
		}
		ImGui::EndCombo();
	}

	if (Resource::Material** mat = (Resource::Material**)DragDropTarget("Material"))
	{
		*material = *mat;
	}

	return false;
}

bool Wrapper::GUI::PickMaterialType(const std::string& label, MaterialType* materialType, bool text)
{
	
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	std::vector<std::string> materialTypeList = {
		"WOOD",
		"BOUNCY_BALL",
		"ICE",
		"RUBBER",
		"ROCK",
		"METAL",
		"GLASS"
	};

	std::string currentMaterialType = Wrapper::ToString(*materialType) ;

	if (ImGui::BeginCombo(("##" + label).c_str(), currentMaterialType.c_str()))
	{
		for (auto str : materialTypeList)
		{
			if (ImGui::Selectable(str.c_str(), str == currentMaterialType))
			{
				*materialType = Wrapper::ToMaterialType(str);
				ImGui::EndCombo();
				return true;
			}
		}
		ImGui::EndCombo();
	}

	return false;
}

bool Wrapper::GUI::PickPostProcessing(const std::string& label, Resource::PostProcessingShader** postPro, bool text)
{

	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	std::vector<std::string> postProNameList = Resource::ResourceManager::GetInstance().GetResourceNameList<Resource::PostProcessingShader>();
	std::string currentPostProName = (*postPro) ? (*postPro)->GetName() : "None";

	if (ImGui::BeginCombo(("##" + label).c_str(), currentPostProName.c_str()))
	{
		if (ImGui::Selectable("None", !postPro))
		{
			*postPro = nullptr;
			ImGui::EndCombo();
			return true;
		}

		for (auto str : postProNameList)
		{
			if (ImGui::Selectable(str.c_str(), str == currentPostProName))
			{
				*postPro = Resource::ResourceManager::GetInstance().GetResource<Resource::PostProcessingShader>(str);
				ImGui::EndCombo();
				return true;
			}
		}
		ImGui::EndCombo();
	}

	if (Resource::PostProcessingShader** mat = (Resource::PostProcessingShader**)DragDropTarget("Post Processing"))
	{
		*postPro = *mat;
	}

	return false;
}

bool Wrapper::GUI::PickCanvas(const std::string& label, UI::Canvas** canvas, bool text)
{
	float textWidth = GUI::CalcTextSize(label.c_str()).x;

	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine(WIDGET_OFFSET * GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x);
	std::string currentPostProName = (*canvas) ? (*canvas)->GetName() : "None";

	if (ImGui::BeginCombo(("##" + label).c_str(), currentPostProName.c_str()))
	{
		if (ImGui::Selectable("None", !canvas))
		{
			*canvas = nullptr;
			ImGui::EndCombo();
			return true;
		}

		for (auto resource : Resource::ResourceManager::GetInstance().GetResourceMap())
		{
			if (resource.second->GetTypeName() == "Canvas")
			{
				auto str = resource.second->GetName();
				if (ImGui::Selectable(str.c_str(), str == currentPostProName))
				{
					*canvas = Resource::ResourceManager::GetInstance().GetResource<UI::Canvas>(str);
					ImGui::EndCombo();
					return true;
				}
			}
			
		}
		ImGui::EndCombo();
	}

	if (UI::Canvas** mat = (UI::Canvas**)DragDropTarget("Canvas"))
	{
		*canvas = *mat;
	}

	return false;
}

bool Wrapper::GUI::PickGameObject(const std::string& label, const std::string& buttonLabel ,int* gameObject, bool text)
{
	
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	if (GUI::Button(buttonLabel.c_str(), Maths::Vec2(100, 20)))
	{
		*gameObject = -1;
	}

	if (Engine::GameObject** go = (Engine::GameObject**)DragDropTarget("GameObject"))
	{
		*gameObject = (*go)->GetID();
		return true;
	}

	return false;
}

bool Wrapper::GUI::PickAudio(const std::string& label, Resource::Audio** audio, bool text)
{
	
	float textWidth = GUI::CalcTextSize(label.c_str()).x;
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine( WIDGET_OFFSET* GUI::GetWindowSize().x);
	}
	ImGui::SetNextItemWidth(NEXT_WIDTH * GUI::GetWindowSize().x );
	std::vector<std::string> meshNameList = Resource::ResourceManager::GetInstance().GetResourceNameList<Resource::Audio>();
	std::string currentMeshName = (*audio) ? (*audio)->GetName() : "None";

	if (ImGui::BeginCombo(("##" + label).c_str(), currentMeshName.c_str()))
	{
		if (ImGui::Selectable("None", !audio))
		{
			*audio = nullptr;
			ImGui::EndCombo();
			return true;
		}

		for (auto str : meshNameList)
		{
			if (ImGui::Selectable(str.c_str(), str == currentMeshName))
			{
				*audio = Resource::ResourceManager::GetInstance().GetResource<Resource::Audio>(str);
				ImGui::EndCombo();
				return true;
			}
		}
		ImGui::EndCombo();
	}
	if (Resource::Audio** newaudio = (Resource::Audio**)DragDropTarget("Audio"))
	{
		*audio = *newaudio;
	}

	return false;
}

void Wrapper::GUI::DisplayText(const char* format, ...)
{
	const int bufferSize = 1024;
	char buffer[bufferSize];

	va_list args;
	va_start(args, format);
	vsnprintf(buffer, bufferSize, format, args);
	va_end(args);

	ImGui::Text(buffer);
}


bool Wrapper::GUI::InputString(const std::string& label, std::string& value, bool enterTrue, bool hiddenName)
{
	const int bufferSize = 256;
	char buffer[bufferSize];

	strncpy_s(buffer, bufferSize, value.c_str(), _TRUNCATE);
	ImGuiInputTextFlags inputTextFlags = ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_AlwaysInsertMode;

	if (enterTrue)
		inputTextFlags |= ImGuiInputTextFlags_EnterReturnsTrue;

	if (hiddenName)
	{
		ImGui::PushID(label.c_str() + 1);
		bool checkbox = ImGui::InputText("", buffer, bufferSize, inputTextFlags);
		value = std::string(buffer);
		ImGui::PopID();
		return checkbox;
	}
	else
	{
		if (ImGui::InputText(label.c_str(), buffer, bufferSize, inputTextFlags))
		{
			value = std::string(buffer);
			return true;
		}
	}
	return false;
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


bool Wrapper::GUI::CheckBox(const std::string& label, bool* isChecked, bool hiddenName)
{

	if (hiddenName)
	{
		ImGui::PushID(label.c_str() + 1);
		ImGui::AlignTextToFramePadding();
		bool checkbox = ImGui::Checkbox("", isChecked);
		ImGui::PopID();
		return checkbox;
	}
	else
	{
		return ImGui::Checkbox(label.c_str(), isChecked);
	}


}

bool Wrapper::GUI::Selectable(const std::string& label, bool isSelected, const Maths::Vec2& size)
{
	return ImGui::Selectable(label.c_str(), &isSelected, 0, ImVec2(size.x, size.y));
}

bool Wrapper::GUI::Combo(const std::string& label, const std::vector<std::string>& list, std::string& selected, bool text, const std::string& first)
{
	if (text)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine();
	}
	if (ImGui::BeginCombo(("##" + label).c_str(), selected.c_str()))
	{
		if (first != "")
		{
			if (ImGui::Selectable(first.c_str(), first == selected))
			{
				selected = first;
				ImGui::EndCombo();
				return true;
			}
		}

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
	}
	return false;
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
	//ImGUITreeNodeFlags
	return ImGui::CollapsingHeader(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen);
}

void Wrapper::GUI::PushID(int ID)
{
	ImGui::PushID(ID);
}

void Wrapper::GUI::PushID(std::string ID)
{
	ImGui::PushID(ID.c_str());
}

void Wrapper::GUI::PopID()
{
	ImGui::PopID();
}

bool Wrapper::GUI::IsItemHovered()
{
	return ImGui::IsItemHovered(ImGuiHoveredFlags_None);
}

bool Wrapper::GUI::IsItemDown(int mouseButton)
{
	return IsItemHovered() && Engine::Input::GetInstance().IsMouseButtonDown(mouseButton);
}

bool Wrapper::GUI::IsItemReleased(int mouseButton)
{
	return IsItemHovered() && Engine::Input::GetInstance().IsMouseButtonReleased(mouseButton);
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

bool Wrapper::GUI::BeginPopup(const std::string& ID, bool isNormalPopUp)
{
	ImGuiWindowFlags notTypicalPopup = ImGuiWindowFlags_None;

	if(!isNormalPopUp)
		notTypicalPopup = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove;

		return ImGui::BeginPopup(ID.c_str(), notTypicalPopup);
}

bool Wrapper::GUI::BeginPopupContextItem(const std::string& ID)
{
	return ImGui::BeginPopupContextItem(ID.c_str());
}

bool Wrapper::GUI::BeginPopupModal(const std::string& ID)
{
	return ImGui::BeginPopupModal(ID.c_str());
}

void Wrapper::GUI::EndPopup()
{
	ImGui::EndPopup();
}

void Wrapper::GUI::CloseCurrentPopUp()
{
	ImGui::CloseCurrentPopup();
}

void Wrapper::GUI::OpenPopup(const std::string& ID)
{
	ImGui::OpenPopup(ID.c_str());
}

void Wrapper::GUI::Demo()
{
	ImGui::ShowDemoWindow();
}

void Wrapper::GUI::MenuBar(std::function<void()> funcTopBar)
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

}

bool Wrapper::GUI::BeginMenu(const char* name)
{
	return ImGui::BeginMenu(name);
}
void Wrapper::GUI::EndMenu()
{
	ImGui::EndMenu();
}

bool Wrapper::GUI::BeginMenuBar()
{
	bool test = ImGui::BeginMenuBar();
	return test;
}

void Wrapper::GUI::EndMenuBar()
{
	ImGui::EndMenuBar();
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


bool Wrapper::GUI::drawGizmo(int mode, float* cameraView, float* cameraProjection, float* matrix, bool editTransformDecomposition)
{
	ImGuizmo::OPERATION gizMod;
	switch (mode)
	{
	case 0:
		gizMod = ImGuizmo::TRANSLATE;
		break;
	case 1:
		gizMod = ImGuizmo::ROTATE;
		break;
	case 2:
		gizMod = ImGuizmo::SCALE;
		break;
	default:
		gizMod = ImGuizmo::TRANSLATE;
		break;
	}

	ImGuizmo::SetID(0);

	//static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
	static bool useSnap = false;
	static float snap[3] = { 1.f, 1.f, 1.f };
	static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
	static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
	static bool boundSizing = false;
	static bool boundSizingSnap = false;

	ImGuizmo::SetDrawlist();
	float windowWidth = (float)ImGui::GetWindowWidth();
	float windowHeight = (float)ImGui::GetWindowHeight();
	ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
	
	//std::cout << ImGuizmo::GetRora << "\n"
	//ImGuizmo::DrawGrid(cameraView, cameraProjection, identityMatrix, 100.f);
	//ImGuizmo::DrawCubes(cameraView, cameraProjection, &objectMatrix[0][0], 1);
	return ImGuizmo::Manipulate(cameraView, cameraProjection, gizMod, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);
}
void Wrapper::GUI::GizmoDecomposeMatrixToComponents(const float* matrix, float* translation, float* rotation, float* scale)
{
	ImGuizmo::DecomposeMatrixToComponents(matrix, translation, rotation, scale);
}