#include "EditorGUI/RendererGUI.hpp"
#include "LowRenderer/Renderer.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/CubeMap.hpp"

void EditorGUI::RendererGUI::DoUpdate()
{
	std::string selected = m_currentScene->GetRenderer()->GetSkybox() ? m_currentScene->GetRenderer()->GetSkybox()->GetName() : "None";
	if (Wrapper::GUI::Combo("Skybox : ", Resource::ResourceManager::GetInstance().GetResourceNameList<Resource::CubeMap>(), selected, "None"))
	{
		if (selected == "None")
		{
			m_currentScene->GetRenderer()->SetSkybox(nullptr);
		}
		else
		{
			Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
			m_currentScene->GetRenderer()->SetSkybox(rm.GetResource<Resource::CubeMap>(selected));
		}
	}
}
