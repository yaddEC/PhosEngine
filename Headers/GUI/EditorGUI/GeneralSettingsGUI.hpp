#pragma once
#pragma once
#include "GUI/IGUI.hpp"
#include <string>
#include <filesystem>
#include <unordered_map>
#include "Wrapper/PhysicsWrapper.hpp"

#include "Engine/Input.hpp"
#include "Engine/Scene.hpp"

namespace Engine
{
	class Scene;
}

namespace Resource
{
	class IResource;
}

namespace EditorGUI
{
	class GeneralSettingsGUI : public APPGUI::IGUI
	{
	public:
		GeneralSettingsGUI();

		~GeneralSettingsGUI();




	private:

		std::string m_newLayerName;
		std::string m_newTagName;
		void DoUpdate() override;

	};
}


