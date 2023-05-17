#include "GUI/EditorGUI/AssetExplorer.hpp"
#include <fstream>
#include "GUI/EditorGUI/PhysicsSettingsGUI.hpp"

namespace fs = std::filesystem;
using namespace std;
using namespace Wrapper;
using namespace EditorGUI;
using namespace Engine;



EditorGUI::PhysicsSettingsGUI::PhysicsSettingsGUI()
	:IGUI("Physics settings", false,false,true)
{
    Wrapper::Physics::LoadLayerInfo();
}

EditorGUI::PhysicsSettingsGUI::~PhysicsSettingsGUI()
{
    Wrapper::Physics::saveLayerInfo();
}



void EditorGUI::PhysicsSettingsGUI::DoUpdate()
{
    std::vector<std::string> layernames = *Wrapper::Physics::GetLayerNames();
    for (const auto& layer1Name : layernames)
    {
        GUI::DisplayText("%s", layer1Name.c_str());

        for (const auto& layer2Name : layernames)
        {
           
            std::string checkBoxID = layer1Name + " vs " + layer2Name;
            bool shouldCollide = Wrapper::Physics::GetLayerCollision(layer1Name, layer2Name);
            
            if (GUI::CheckBox(checkBoxID.c_str(), &shouldCollide))
            {     
                    Wrapper::Physics::SetLayerCollision(layer1Name, layer2Name, shouldCollide);
            }
        }
    }

    GUI::InputString("New Layer Name", newLayerName);

    if (GUI::Button("Create Layer"))
    {
        Wrapper::Physics::CreateLayer(newLayerName);
        //newLayerName = "";
    }
}
