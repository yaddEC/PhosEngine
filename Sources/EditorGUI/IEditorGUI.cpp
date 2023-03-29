#include "EditorGUI/IEditorGUI.hpp"


using namespace EditorGUI;

void IEditorGUI::Update() 
{
	if (isOpen)
	{
		//ImGui::Begin(name.c_str(), 0, ImGuiWindowFlags_NoCollapse);
		GUI::BeginWindow(name, false);

		SetSize();
		SetIsOnFocus();

		DoUpdate();

		GUI::EndWindow();
	}
}