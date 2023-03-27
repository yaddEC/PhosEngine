#pragma once
#include <vector>
#include <string>
#include "LowRenderer/Camera.hpp"
#include "Maths/Maths.hpp"

#ifdef SCENE_EXPORTS
#define SCENE_API __declspec(dllexport)
#else
#define SCENE_API __declspec(dllimport)
#endif


namespace LowRenderer
{
	class MeshRenderer;
	class Renderer;
}




namespace Engine
{
	class GameObject;

	class SCENE_API Scene
	{
	public:

		Scene();

		void Update();
		
		GameObject* Instantiate(GameObject* newGameObject);

		LowRenderer::Renderer* GetRenderer() { return renderer; }

		bool GetIsGameMode() { return m_IsGameMode; }

		std::vector<GameObject*> GetGameObjects() { return m_gameObjects; }


	private:
		std::vector<GameObject*> m_gameObjects;
		std::vector<GameObject*> m_gameObjectBuffer;

		LowRenderer::Renderer* renderer;
		bool m_IsGameMode = false;
	};
}
