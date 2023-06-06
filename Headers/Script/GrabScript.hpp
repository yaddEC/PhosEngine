#pragma once
#include "Engine/MonoBehaviour.hpp"
namespace Physic
{
	class Rigidbody;
}

namespace Engine
{
	class GameObject;
	class Input;

}

namespace Script
{
	class PlayerMouvement;

}
namespace Physic
{
	class SphereCollider;

}

namespace Script
{
	class PHOSENGINE_API GrabScript : public Engine::MonoBehaviour
	{
	public:
		GrabScript();
		~GrabScript();
		void Start() override;

		void OnTriggerEnter(Engine::GameObject* go)  override;

		void OnTriggerExit(Engine::GameObject* go)  override;

		void Update() override;
		//void OnInspector() override;
		Reflection::ClassMetaData& GetMetaData() override;
	private:
		Maths::Vec3 m_grabOffset;
		Script::PlayerMouvement* m_playerMouvement;
		Engine::GameObject* m_actualObject;
		Engine::GameObject* m_player;
		bool m_isPressed;
		Engine::Input* m_input;
		Maths::Vec3 m_currPos;
		Maths::Vec3 m_prevPos;
		Maths::Vec3 m_velocity;
		Physic::Rigidbody* m_grabbedRB;
		Physic::SphereCollider* m_selfCollider;
		Engine::Transform m_relativeTransform;
	};


}