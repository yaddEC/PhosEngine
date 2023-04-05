#pragma once
#include "IResource.hpp"
#include <vector>

#ifdef PREFAB_EXPORTS
#define PREFAB_API __declspec(dllexport)
#else
#define PREFAB_API __declspec(dllimport)
#endif

namespace Engine
{
	class GameObject;
}

namespace Resource
{

	class PREFAB_API Prefab : public IResource
	{
	public:

		Prefab() : IResource() {};
		~Prefab() {};

		void Load(const std::string& filepath) override;
		void Bind() override;
		void Unload() override;
		void Save() override;
		void GUIUpdate() override;
		Texture* GenerateFileIcon() override;
		std::vector<Engine::GameObject*> gameObjectList;

	private:

		Engine::GameObject* ParseGameObject(const std::vector<std::string>& fileData, size_t& lineIndex);
	};
}
