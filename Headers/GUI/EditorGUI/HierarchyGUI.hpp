#pragma once
#include "GUI/IGUI.hpp"
#include "Engine/Scene.hpp"
#include "Engine/GameObject.hpp"

namespace EditorGUI
{
	class HierarchyGUI : public APPGUI::IGUI
	{
	public:
		HierarchyGUI();

		void SetCurrentScene(Engine::Scene* newScene) { m_currentScene = newScene; }

		void DoUpdate() override;
		Engine::GameObject* GetSelected();
		bool selectedClicked = false;

	private:
		Engine::Scene* m_currentScene;
		Engine::GameObject* m_selected;

		void DisplayHierarchy(Engine::GameObject* current);
		void AddObjectPopup(Engine::GameObject* current);
	};
}
