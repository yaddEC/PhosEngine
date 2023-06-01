#pragma once

#include "Engine/MonoBehaviour.hpp"

namespace Engine
{
	class GamepadInput;
}

namespace Script
{
	class PlayerMouvement;

	class PHOSENGINE_API InputManager : public Engine::MonoBehaviour
	{
	public:
		InputManager();
		~InputManager();
		void Start() override;
		void Update() override;
		void GUIUpdate() override;
		void OnInspector() override;
		void OnDestroy() override;
		Reflection::ClassMetaData& GetMetaData() override;
	private:
		Engine::GamepadInput* gamepads;
		std::vector<PlayerMouvement*> playerMovement;
		
	};
	

}
