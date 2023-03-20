#include "EditorGUI/HierarchyGUI.hpp"
#include "Wrapper/GUI.hpp"


void EditorGUI::HierarchyGUI::DoUpdate()
{
	DisplayHierarchy();
	
}

void EditorGUI::HierarchyGUI::DisplayHierarchy()
{
	if (GUI::BeginPopupContextItem("Test"))
	{
		GUI::DisplayText("Example text");
		GUI::EndPopup();
	}


}
