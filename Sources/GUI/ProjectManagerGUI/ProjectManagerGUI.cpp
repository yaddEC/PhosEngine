#include "GUI/ProjectManagerGUI/ProjectManagerGUI.hpp"

ProjectManagerGUI::ProjectManagerGUI::ProjectManagerGUI() :
	IGUI("Hierarchy", true)
{

}

void ProjectManagerGUI::ProjectManagerGUI::DoUpdate()
{
	Wrapper::GUI::DisplayText("Add GameObject");

}