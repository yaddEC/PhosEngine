#include "GUI\EditorGUI\InputGUI.hpp"
#include "Engine/Input.hpp"

EditorGUI::InputGUI::InputGUI() : IGUI("Input", false)
{
}

void EditorGUI::InputGUI::DoUpdate()
{
	Engine::Input& inputManager = Engine::Input::GetInstance();
	inputManager.DisplayGUI();
}