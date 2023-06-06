#pragma once

#include "Engine/MonoBehaviour.hpp"

namespace Engine
{
	class GameObject;
}

namespace Script
{
	class PHOSENGINE_API WinZone : public Engine::MonoBehaviour
	{
	public:
		WinZone();
		~WinZone();
		void OnInspector() override;
		void OnTriggerEnter(Engine::GameObject* go) override;
		void OnTriggerExit(Engine::GameObject* go)override;
		Reflection::ClassMetaData& GetMetaData() override;

	private:
		bool m_leftSide;
	};


}