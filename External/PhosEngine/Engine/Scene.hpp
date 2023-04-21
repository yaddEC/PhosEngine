#pragma once
#include <vector>
#include <string>
#include "LowRenderer/Camera.hpp"
#include "Maths/Maths.hpp"
#include "Physic/PhysicsManager.hpp"
#include "Resource/IResource.hpp"

#include "dllInclude.hpp"


namespace Resource
{
	class Prefab;
	class Texture;
}

namespace LowRenderer
{
	class MeshRenderer;
	class Renderer;
}



namespace Engine
{
	class GameObject;

	class PHOSENGINE_API Scene : public Resource::IResource
	{
	public:

		Scene();
		~Scene();

		void Update();
		
		GameObject* Instantiate(GameObject* newGameObject);
		GameObject* InstantiatePrefab(const Resource::Prefab& prefab);


		void DeleteGameObjectFromList(GameObject* go);

		LowRenderer::Renderer* GetRenderer() { return m_renderer; }

		bool GetIsGameMode() { return m_IsGameMode; }

		std::vector<GameObject*> GetGameObjects() { return m_gameObjects; }

		void Load(const std::string& filepath) override;
		void Bind() override {}
		void Unload() override;
		void Save() override;
		void GUIUpdate() override {}
		std::string GetTypeName() { return "Scene"; }
		Resource::Texture* GenerateFileIcon() override { return nullptr; }


	private:
		void GameObjectFromBuffer();

		void SaveGameObject(Engine::GameObject* gameObject, std::fstream& file, int depth = 0);
		GameObject* ParseGameObject(const std::vector<std::string>& fileData, size_t& lineIndex);

		std::vector<GameObject*> m_gameObjects;
		std::vector<GameObject*> m_gameObjectBuffer;

		LowRenderer::Renderer* m_renderer;
		bool m_IsGameMode = false;
	};
}

