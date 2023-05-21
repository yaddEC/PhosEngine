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
   
}

EditorGUI::PhysicsSettingsGUI::~PhysicsSettingsGUI()
{
   
}



void EditorGUI::PhysicsSettingsGUI::DoUpdate()
{
    GUI::BeginGroup();
    GUI::EndGroup();
    std::vector<std::string> layernames = *Wrapper::Physics::GetLayerNames();
    if(layernames.size()>0)
    { 
    GUI::BeginGroup();
    GUI::BeginGroup();
    GUI::DisplayText("\n \n");
    GUI::EndGroup();
    for (int i = 0; i < layernames.size(); i++)
    {
    GUI::SameLine();
    GUI::BeginGroup();
    
        GUI::DisplayText("%s\n\n", layernames[i].c_str());

        for (int j = 0; j<=i; j++)
        {
            bool hiddenName = true;
            std::string checkBoxID = layernames[j] + to_string(j) + to_string(i);;
            if (i == layernames.size() - 1)
            {
                hiddenName = false;
                checkBoxID = layernames[j];
            }
                
            bool shouldCollide = Wrapper::Physics::GetLayerCollision(layernames[i], layernames[j]);
            if (GUI::CheckBox(checkBoxID.c_str(), &shouldCollide,hiddenName))
            {     
                    Wrapper::Physics::SetLayerCollision(layernames[i], layernames[j], shouldCollide);
            }

            

        }
    GUI::EndGroup();
    }

    GUI::EndGroup();
    }
}
