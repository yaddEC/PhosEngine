#include "EditorGUI/IEditorGUI.h"


void IEditorGUI::Update()
{
	if (isOpen)
	{
		ImGui::Begin(name.c_str(), 0, ImGuiWindowFlags_NoCollapse);

		SetSize();
		SetIsOnFocus();

		DoUpdate();

		ImGui::End();
	}
}