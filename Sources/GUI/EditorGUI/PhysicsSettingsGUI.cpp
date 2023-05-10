#include "GUI/EditorGUI/AssetExplorer.hpp"

#include <fstream>
#include "GUI/EditorGUI/PhysicsSettingsGUI.hpp"

namespace fs = std::filesystem;
using namespace std;
using namespace Wrapper;
using namespace EditorGUI;
using namespace Engine;



EditorGUI::PhysicsSettingsGUI::PhysicsSettingsGUI()
	:IGUI("Physics settings", true,true)
{
}

EditorGUI::PhysicsSettingsGUI::~PhysicsSettingsGUI()
{
}



void EditorGUI::PhysicsSettingsGUI::DoUpdate()
{
   
}
