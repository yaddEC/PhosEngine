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

		void StartGameMode();
		void StopGameMode();

		void Load() override;
		void Bind() override {}
		void Unload() override;
		void Save() override;
		void GUIUpdate() override {}

		static void SaveSettings();
		static void LoadSettings();

		GameObject* FindGameObjectWithId(unsigned int id);
		std::vector<GameObject*> FindAllGameObjectWithTag(const std::string tagName);

		std::string GetTypeName() { return "Scene"; }
		Resource::Texture* GenerateFileIcon() override { return nullptr; }

		static void CreateTag(const std::string tagName);
		static std::string GetTagName(unsigned int Layer);
		static std::vector<std::string> tagNames;
		static std::map<std::string, unsigned int> tagNameToIndexMap;


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

