#include "GUI/EditorGUI/InspectorGUI.hpp"
#include "Engine/Transform.hpp"
#include "Engine/MonoBehaviour.hpp"
#include "LowRenderer/CameraComponent.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Texture.hpp"
#include "Physic/Collider.hpp"
#include "Physic/Rigidbody.hpp"
#include "Physic/Joint.hpp"
#include "Script/PlayerMouvement.hpp"
#include "Script/InputManager.hpp"
#include "LowRenderer/MeshRenderer.hpp"
#include "LowRenderer/Light/DirectionalLight.hpp"
#include "LowRenderer/Light/SpotLight.hpp"
#include "LowRenderer/Light/PointLight.hpp"
#include "Sound/SoundPlayer.hpp"

#include <typeinfo>

namespace Maths
{
	class Vec3;
}

using namespace Wrapper;
using namespace Maths;

EditorGUI::InspectorGUI::InspectorGUI() : IGUI("Inspector", true)
{

}

void EditorGUI::InspectorGUI::DeselectCurrentGameObject()
{
	m_gameobject = nullptr;
}

void EditorGUI::InspectorGUI::DeselectCurrentAsset()
{
	m_resource = nullptr;
}

void EditorGUI::InspectorGUI::DoUpdate()
{
	if (m_typeToDisplay == ObjectType::GAME_OBJECT)
	{
		DisplayGameObject();
	}
	else if (m_typeToDisplay == ObjectType::RESOURCE)
	{
		DisplayResource();
	}
}


void EditorGUI::InspectorGUI::DisplayGameObject()
{
	if (!m_gameobject) return;

	GUI::BeginGroup();
	Wrapper::GUI::DisplayText(m_gameobject->name.c_str());

	std::vector<std::string> layerNames = *Wrapper::Physics::GetLayerNames();
	std::string layerSelected = Wrapper::Physics::GetLayerName(m_gameobject->GetLayer());
	std::string tagSelected = Engine::Scene::GetTagName(m_gameobject->GetTag());
	GUI::BeginGroup();
	Wrapper::GUI::DisplayText("Tag");
	GUI::SetNextItemWidth(GUI::GetWindowSize().x * 0.4f);
	if (GUI::Combo("Tag", Engine::Scene::tagNames, tagSelected))
	{
		m_gameobject->SetTag(Engine::Scene::tagNameToIndexMap[tagSelected]);
	}

	GUI::EndGroup();
	GUI::SameLine();
	GUI::BeginGroup();
	Wrapper::GUI::DisplayText("Layer");
	GUI::SetNextItemWidth(GUI::GetWindowSize().x * 0.4f);
	if (GUI::Combo("Layer", layerNames, layerSelected))
	{
		m_gameobject->SetLayer(Wrapper::Physics::GetLayerID(layerSelected));
	}
	GUI::EndGroup();
	GUI::EndGroup();

	Wrapper::GUI::Separator();
	if (Wrapper::GUI::CollapsingHeader("Transform"))
	{
		m_gameobject->transform->OnGUI();
	}

	for (Engine::MonoBehaviour* component : m_gameobject->GetComponents())
	{
		GUI::BeginGroup();
		component->OnInspector();
		GUI::EndGroup();
	}

	GUI::BeginGroup();
	if (GUI::Button("Add Component"))
	{
		GUI::OpenPopup("Add Component");
	}
	GUI::EndGroup();

	if (GUI::BeginPopup("Add Component"))
	{
		if (GUI::Selectable("Rigid Body", false))
		{
			m_gameobject->AddComponent<Physic::Rigidbody>();
		}

		if (GUI::BeginMenu("Colliders"))
		{
			if (GUI::MenuItem("Sphere Collider", nullptr))
			{
				m_gameobject->AddComponent<Physic::SphereCollider>();
			}
			if (GUI::MenuItem("Capsule Collider", nullptr))
			{
				m_gameobject->AddComponent<Physic::CapsuleCollider>();
			}
			if (GUI::MenuItem("Box Collider", nullptr))
			{
				m_gameobject->AddComponent<Physic::BoxCollider>();
			}
			GUI::EndMenu();
		}

		if (GUI::BeginMenu("Joints"))
		{
			if (GUI::MenuItem("Fixed Joints", nullptr))
			{
				m_gameobject->AddComponent<Physic::FixedJoint>();
			}
			if (GUI::MenuItem("Hinge Joints", nullptr))
			{
				m_gameobject->AddComponent<Physic::HingeJoint>();
			}
			if (GUI::MenuItem("Spring Joints", nullptr))
			{
				m_gameobject->AddComponent<Physic::SpringJoint>();
			}
			if (GUI::MenuItem("Custom Joints", nullptr))
			{
				m_gameobject->AddComponent<Physic::ConfigurableJoint>();
			}
			GUI::EndMenu();
		}
		if (GUI::BeginMenu("Light"))
		{
			if (GUI::MenuItem("Spot Light", nullptr))
			{
				m_gameobject->AddComponent<LowRenderer::SpotLight>();
			}
			if (GUI::MenuItem("Directional Light", nullptr))
			{
				m_gameobject->AddComponent<LowRenderer::DirectionalLight>();
			}
			if (GUI::MenuItem("Point Light", nullptr))
			{
				m_gameobject->AddComponent<LowRenderer::PointLight>();
			}
			GUI::EndMenu();
		}
		if (GUI::Selectable("Mesh Renderer", false))
		{
			m_gameobject->AddComponent<LowRenderer::MeshRenderer>();
		}
		if (GUI::Selectable("Camera Component", false))
		{
			m_gameobject->AddComponent<LowRenderer::CameraComponent>();
		}
		if (GUI::Selectable("Sound", false))
		{
			m_gameobject->AddComponent<Sound::SoundPlayer>();
		}
		if (GUI::BeginMenu("Script"))
		{
			if (GUI::MenuItem("Player Movement", nullptr))
			{
				m_gameobject->AddComponent<Script::PlayerMouvement>();
			}
			if (GUI::MenuItem("Input Manager", nullptr))
			{
				m_gameobject->AddComponent<Script::InputManager>();
			}
			GUI::EndMenu();
		}
		GUI::EndPopup();
	}
}

void EditorGUI::InspectorGUI::DisplayResource()
{
	if (!m_resource) return;
	Wrapper::GUI::SetWindowFontSize(2.f);
	Wrapper::GUI::DisplayText(m_resource->GetName().c_str());
	Wrapper::GUI::DisplayText(m_resource->isBinded && m_resource->isLoaded ? "Yes" : "No");
	Wrapper::GUI::SetWindowFontSize(1);
	Wrapper::GUI::SetCursorPos(Wrapper::GUI::GetCursorPos() + Maths::Vec2(0, 5));
	Wrapper::GUI::Separator();
	m_resource->GUIUpdate();
}
