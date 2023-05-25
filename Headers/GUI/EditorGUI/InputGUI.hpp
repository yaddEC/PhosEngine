#pragma once
#include "GUI/IGUI.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"
#include "Resource/IResource.hpp"
#include "Wrapper/PhysicsWrapper.hpp"



namespace EditorGUI
{
	class InputGUI : public APPGUI::IGUI
	{
	public:
		InputGUI() ;

		void DoUpdate() override;

	private:

	};
}
