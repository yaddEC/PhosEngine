#include "GUI/EditorGUI/AssetExplorer.hpp"
#include <fstream>
#include "GUI/EditorGUI/GeneralSettingsGUI.hpp"

namespace fs = std::filesystem;
using namespace std;
using namespace Wrapper;
using namespace EditorGUI;
using namespace Engine;



EditorGUI::GeneralSettingsGUI::GeneralSettingsGUI()
    :IGUI("General settings", false, false, true)
{
    Engine::Scene::LoadSettings();
}

EditorGUI::GeneralSettingsGUI::~GeneralSettingsGUI()
{
    Engine::Scene::SaveSettings();
}



void EditorGUI::GeneralSettingsGUI::DoUpdate()
{
    GUI::DisplayText("Layers\n");
    GUI::SetNextItemWidth(100);
    if (GUI::InputString("Layers", m_newLayerName,true,true) && m_newLayerName != "" && m_newLayerName.c_str()[0] != ' ')
    {
        Wrapper::Physics::CreateLayer(m_newLayerName);
        m_newLayerName = "";
    }
    std::vector<std::string> layernames = *Wrapper::Physics::GetLayerNames();
    
    for (int i = 0; i < layernames.size(); i++)
    {
        GUI::DisplayText("%s\n", layernames[i].c_str());
    }
    GUI::DisplayText("\n");
    GUI::DisplayText("Tags\n");
    GUI::SetNextItemWidth(100);
    if (GUI::InputString("Tags", m_newTagName, true, true) && m_newTagName != "" && m_newTagName.c_str()[0] != ' ')
    {
        Engine::Scene::CreateTag(m_newTagName);
        m_newTagName = "";
    }

    for (int i = 0; i < Engine::Scene::tagNames.size(); i++)
    {
        GUI::DisplayText("%s\n", Engine::Scene::tagNames[i].c_str());
    }


}
