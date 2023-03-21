#pragma once
#include "EditorGUI/IEditorGUI.hpp"
#include "Engine/GameObject.hpp"
#include "Resource/IResource.hpp"

namespace EditorGUI
{
	class InspectorGUI : public IEditorGUI
	{
	public:
		InspectorGUI() : IEditorGUI("Inspector") {}

		void SetGameObjectToDisplay(Engine::GameObject* gameObject) { m_gameobject = gameObject; m_typeToDisplay = ObjectType::GAME_OBJECT; }
		void SetResourceToDisplay(Resource::IResource* resource) { m_resource = resource; m_typeToDisplay = ObjectType::RESOURCE; }
		void DoUpdate() override;

	private:

		union
		{
			Engine::GameObject* m_gameobject;
			Resource::IResource* m_resource;
		};

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