#pragma once

#include "Engine/MonoBehaviour.hpp"
namespace Physic
{
	class Rigidbody;
}

namespace Script
{
	class PHOSENGINE_API PlayerMouvement : public Engine::MonoBehaviour
	{
	public:
		PlayerMouvement();
		~PlayerMouvement();
		void Start() override;
		void Update() override;
		void OnInspector() override;
		void SetController(Engine::Controller ID);
		int GetController() { return (int)m_controller; }
		Reflection::ClassMetaData& GetMetaData() override;
	private:
		float m_playerSpeed, m_lookSpeedGamepad, m_lookSpeedMouse, m_jumpeForce;
		Engine::Controller m_controller = Engine::Controller::C_NONE;
		Engine::Transform* m_cameraCenter;
		Physic::Rigidbody* m_rb;
		Engine::Transform* m_mesh;
		Engine::Transform* m_groundCheck;
		bool m_isGrounded;
	};


}