#include "EditorGUI/IEditorGUI.hpp"

using namespace EditorGUI;

void IEditorGUI::Update()
{
	if (isOpen)
	{
		ImGui::Begin(name.c_str(), 0, ImGuiWindowFlags_NoCollapse);
		ImGui::Text("example text");
		SetSize();
		SetIsOnFocus();

		DoUpdate();

		ImGui::End();
	}
}