#include "GUI/IGUI.hpp"


using namespace Wrapper;

void APPGUI::IGUI::Update()
{
	if (isOpen)
	{
		
		Wrapper::GUI::BeginWindow(p_name, false);
		if (p_canBeClosed)
		{
			if (GUI::TitleButton())
				isOpen = false;
		}

		SetSize();
		SetIsOnFocus();

		DoUpdate();

		Wrapper::GUI::EndWindow();
	}
}