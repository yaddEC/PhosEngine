#pragma once
#include "GUI/IGUI.hpp"
#include <string>
#include <filesystem>
#include <unordered_map>


#include "Engine/Input.hpp"

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
	class PhysicsSettingsGUI : public APPGUI::IGUI
	{
	public:
		PhysicsSettingsGUI();

		~PhysicsSettingsGUI();

		


	private:

		void DoUpdate() override;

	};
}


