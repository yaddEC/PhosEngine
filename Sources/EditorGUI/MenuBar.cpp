#include "EditorGUI/MenuBar.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Texture.hpp"

EditorGUI::MenuBar::MenuBar()
{

}

EditorGUI::MenuBar::~MenuBar()
{

}

void Top()
{
	if (GUI::BeginMenu("File"))
	{
		if (GUI::MenuItem("New Project...", NULL)) {}
		if (GUI::MenuItem("Open Project...", NULL)) {}
		if (GUI::MenuItem("Save Project", NULL)) {}
		GUI::Separator();
		if (GUI::MenuItem("Exit", "Alt+F4")) {}
		GUI::EndMenu();
	}
	if (GUI::BeginMenu("Window"))
	{
		if (GUI::MenuItem("Assets Explorer", NULL, true)) {}
		if (GUI::MenuItem("Hierarchy", NULL, true)) {}
		if (GUI::MenuItem("Inspector", NULL, true)) {}
		if (GUI::MenuItem("Scene", NULL, true)) {}
		GUI::EndMenu();
	}
	if (GUI::BeginMenu("Help"))
	{
		if (GUI::MenuItem("About Phos", NULL)) {}
		GUI::Separator();
		if (GUI::MenuItem("Phos Manual", NULL)) {}
		if (GUI::MenuItem("Scripting Reference", NULL)) {}
		GUI::EndMenu();
	}
}

void Bottom()
{
	GUI::BeginGroupCentered((40,20));
	GUI::Image(*Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("Assets\\Texture\\play.png"), { 20, 20 });
	GUI::Image(*Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("Assets\\Texture\\pause.png"), { 20, 20 });
	GUI::EndGroup();
}

void EditorGUI::MenuBar::Update()
{
	GUI::MenuBar(Top, Bottom);
	//GUI::Demo();
}