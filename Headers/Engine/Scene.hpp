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
}




namespace Engine
{
	class GameObject;
	class Renderer;

	class SCENE_API Scene
	{
	public:

		Scene();

		void Update();
		GameObject& Instantiate(GameObject* newGameObject);

		inline std::vector<LowRenderer::MeshRenderer*> GetModelList() { return modelList; }
		inline void AddModel(LowRenderer::MeshRenderer* model) { modelList.push_back(model); }


	private:
		std::vector<LowRenderer::MeshRenderer*> modelList;
		std::vector<GameObject*> m_gameObjects;
	};
}

