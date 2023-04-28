#include "GUI/IGUI.hpp"


using namespace Wrapper;

void APPGUI::IGUI::Update()
{
	if (isOpen)
	{
		//ImGui::Begin(name.c_str(), 0, ImGuiWindowFlags_NoCollapse);
		Wrapper::GUI::BeginWindow(p_name, false);

		SetSize();
		SetIsOnFocus();

		DoUpdate();

		Wrapper::GUI::EndWindow();
	}
}