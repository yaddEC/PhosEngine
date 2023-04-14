#pragma once
#include "IResource.hpp"
#include <vector>
#include <fstream>
#include "dllInclude.hpp"

namespace Engine
{
	class GameObject;
}

namespace Resource
{

	class PHOSENGINE_API Prefab : public IResource
	{
	public:

		Prefab() : IResource() {};
		~Prefab() {};

		void Load(const std::string& filepath) override;
		void Bind() override;
		void Unload() override;
		void Save() override;
		void GUIUpdate() override;
		std::string GetTypeName() { return "Prefab"; }
		Texture* GenerateFileIcon() override;

		std::vector<Engine::GameObject*> GetCopy();


		static void SaveGameObjectAsPrefab(Engine::GameObject* gameObject, std::fstream& file, int depth = 0);
	private:

		std::vector<Engine::GameObject*> gameObjectList;
		Engine::GameObject* ParseGameObject(const std::vector<std::string>& fileData, size_t& lineIndex);
	};
}
