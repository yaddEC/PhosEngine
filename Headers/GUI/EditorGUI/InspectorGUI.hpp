#pragma once
#include "GUI/IGUI.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"
#include "Resource/IResource.hpp"
#include "Wrapper/PhysicsWrapper.hpp"



namespace EditorGUI
{
	class InspectorGUI : public APPGUI::IGUI
	{
	public:
		InspectorGUI();

		void SetGameObjectToDisplay(Engine::GameObject* gameObject) { m_gameobject = gameObject; m_typeToDisplay = ObjectType::GAME_OBJECT; }
		void SetResourceToDisplay(Resource::IResource* resource) { m_resource = resource; m_typeToDisplay = ObjectType::RESOURCE; }
		void DeselectCurrentGameObject();
		void DeselectCurrentAsset();
		void DoUpdate() override;


	private:

		
			Engine::GameObject* m_gameobject;
			Resource::IResource* m_resource;
		

		enum class ObjectType
		{
			GAME_OBJECT,
			RESOURCE
		};

		ObjectType m_typeToDisplay;


		void DisplayGameObject();
		void DisplayResource();

	};
}