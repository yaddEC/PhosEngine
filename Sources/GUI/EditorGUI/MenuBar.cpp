 #include "GUI/EditorGUI/MenuBar.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Texture.hpp"
#include "Engine/Scene.hpp"

using namespace Wrapper;

EditorGUI::MenuBar::MenuBar()
{

}

EditorGUI::MenuBar::~MenuBar()
{

}

void Top()
{
	if (Wrapper::GUI::BeginMenu("File"))
	{
		if (Wrapper::GUI::MenuItem("New Project...", NULL)) {}
		if (Wrapper::GUI::MenuItem("Open Project...", NULL)) {}
		if (Wrapper::GUI::MenuItem("Save Project", NULL))
		{
			Resource::ResourceManager::GetInstance().Save();
		}
		Wrapper::GUI::Separator();
		if (Wrapper::GUI::MenuItem("Exit", "Alt+F4")) {}
		Wrapper::GUI::EndMenu();
	}
	if (Wrapper::GUI::BeginMenu("Window"))
	{
		if (Wrapper::GUI::MenuItem("Assets Explorer", NULL, true)) {}
		if (Wrapper::GUI::MenuItem("Hierarchy", NULL, true)) {}
		if (Wrapper::GUI::MenuItem("Inspector", NULL, true)) {}
		if (Wrapper::GUI::MenuItem("Scene", NULL, true)) {}
		Wrapper::GUI::EndMenu();
	}
	if (Wrapper::GUI::BeginMenu("Help"))
	{
		if (Wrapper::GUI::MenuItem("About Phos", NULL)) {}
		Wrapper::GUI::Separator();
		if (Wrapper::GUI::MenuItem("Phos Manual", NULL)) {}
		if (Wrapper::GUI::MenuItem("Scripting Reference", NULL)) {}
		Wrapper::GUI::EndMenu();
	}
}

void Bottom()
{
	Wrapper::GUI::BeginGroupCentered((40, 20));
	Wrapper::GUI::Image(*Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("Assets\\Texture\\play.png"), { 20, 20 });
	Wrapper::GUI::Image(*Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("Assets\\Texture\\pause.png"), { 20, 20 });
	Wrapper::GUI::EndGroup();
}

void EditorGUI::MenuBar::Update()
{
	Wrapper::GUI::MenuBar(Top, Bottom);
	//Wrapper::GUI::Demo();
}