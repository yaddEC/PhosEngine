#pragma once
#include "EditorGUI/IEditorGUI.hpp"
#include "Engine/Scene.hpp"
#include "Engine/GameObject.hpp"

namespace EditorGUI
{
	class HierarchyGUI : public IEditorGUI
	{
	public:
		HierarchyGUI();

		void SetCurrentScene(Engine::Scene* newScene) { m_currentScene = newScene; }

		void DoUpdate() override;
		Engine::GameObject* GetSelected();

	private:
		Engine::Scene* m_currentScene;
		Engine::GameObject* m_selected;
		bool m_selectedClicked = false;

		void DisplayHierarchy(Engine::GameObject* current);
	};
}
