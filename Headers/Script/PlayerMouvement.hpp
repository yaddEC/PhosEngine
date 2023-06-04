#pragma once

#include "Engine/MonoBehaviour.hpp"

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
		float m_playerSpeed, m_lookSpeedGamepad, m_lookSpeedMouse;
		Engine::Controller m_controller = Engine::Controller::C_NONE;
		Engine::Transform* m_cameraCenter;
	};


}