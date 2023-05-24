#pragma once
#include "GUI/IGUI.hpp"
#include <string>
#include <filesystem>
#include <unordered_map>
#include "Wrapper/PhysicsWrapper.hpp"

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
		Maths::Vec3 m_gravity = Maths::Vec3(0,-9.81f,0);
	};
}


