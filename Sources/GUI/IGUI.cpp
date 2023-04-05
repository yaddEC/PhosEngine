#include "GUI/IGUI.hpp"


using namespace Wrapper;
using namespace EditorGUI;

void IGUI::Update() 
{
	if (isOpen)
	{
		//ImGui::Begin(name.c_str(), 0, ImGuiWindowFlags_NoCollapse);
		Wrapper::GUI::BeginWindow(name, false);

		SetSize();
		SetIsOnFocus();

		DoUpdate();

		Wrapper::GUI::EndWindow();
	}
}