#pragma once

#include "Engine/MonoBehaviour.hpp"

namespace Engine
{
	class GameObject;
}

namespace Script
{
	class PHOSENGINE_API DeathDetection : public Engine::MonoBehaviour
	{
	public:
		DeathDetection();
		~DeathDetection();
		void OnTriggerEnter(Engine::GameObject* go) override;
		void OnInspector() override;
		Reflection::ClassMetaData& GetMetaData() override;
	private:

	};


}
