#include "GUI/IGUI.hpp"


using namespace Wrapper;

void APPGUI::IGUI::Update()
{
	if (isOpen)
	{
		
		Wrapper::GUI::BeginWindow(p_name, false, p_isDialogBox,p_canBeClosed, &isOpen);




		SetSize();
		SetIsOnFocus();

		DoUpdate();

		Wrapper::GUI::EndWindow();
	}
}