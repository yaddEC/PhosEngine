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
		void SetSelected(Engine::GameObject* selected) { m_selected = selected; }
		bool selectedClicked = false;

	private:
		Engine::Scene* m_currentScene;
		Engine::GameObject* m_selected;
		Engine::GameObject* m_renaming = nullptr;

		std::vector<std::pair<Engine::GameObject*, Engine::GameObject*>> m_objectToParentBuffer;
		std::vector<Engine::GameObject*> m_bufferToDestroy;

		void DisplayHierarchy(Engine::GameObject* current);
		void AddObjectPopup(Engine::GameObject* current);
	};
}
