// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/Texture.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Transform.hpp"
#include "Engine/MonoBehaviour.hpp"

#include "Resource/Parser.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#define PREFAB_EXPORTS
#include "Resource/Prefab.hpp"


using namespace Resource;

void Resource::Prefab::Load(const std::string& filepath)
{
	std::vector<std::string> fileData = Parser::ConvertFileToStringArray(filepath);
	size_t lineIndex = 0;
	ParseGameObject(fileData, lineIndex);
}

void Resource::Prefab::Bind()
{

}

void Resource::Prefab::Unload()
{

}

void Resource::Prefab::Save()
{

}

void Resource::Prefab::GUIUpdate()
{

}

Texture* Resource::Prefab::GenerateFileIcon()
{
	return nullptr;
}

Engine::GameObject* Resource::Prefab::ParseGameObject(const std::vector<std::string>& fileData, size_t& lineIndex)
{
	using namespace Engine;
	GameObject* newGameObject = new GameObject();
	gameObjectList.push_back(newGameObject);
	for (; lineIndex < fileData.size(); lineIndex++)
	{
		std::vector<std::string> tokens = Parser::Tokenize(fileData[lineIndex], ' ', '\t');
		
		if (tokens[0] == "name")
		{
			newGameObject->name = tokens[1];
		}
		else if (tokens[0] == "id")
		{
			newGameObject->SetID(std::stof(tokens[1]));
		}
		else if (tokens[0] == "trans")
		{
			newGameObject->transform->position = Maths::Vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
			newGameObject->transform->rotation = Maths::Vec3(std::stof(tokens[4]), std::stof(tokens[5]), std::stof(tokens[6]));
			newGameObject->transform->scale = Maths::Vec3(std::stof(tokens[7]), std::stof(tokens[8]), std::stof(tokens[9]));
		}
		else if (tokens[0] == "child")
		{
			newGameObject->transform->AddChild(ParseGameObject(fileData, ++lineIndex)->transform);
		}
		else if (tokens[0] == "end")
		{
			return newGameObject;
		}
	}
	
}

void Resource::Prefab::SaveGameObjectAsPrefab(Engine::GameObject* gameObject, std::fstream& file)
{

	std::cout << "name " << gameObject->name << '\n'
		<< "id " << gameObject->GetID() << '\n'
		<< "trans " << gameObject->transform->position.x << ' ' << gameObject->transform->position.y << ' ' << gameObject->transform->position.z 
		<< ' ' << gameObject->transform->rotation.x << ' ' << gameObject->transform->rotation.y << ' ' << gameObject->transform->rotation.z
		<< ' ' << gameObject->transform->scale.x << ' ' << gameObject->transform->scale.y << ' ' << gameObject->transform->scale.z << '\n';
	for (auto comp : gameObject->GetComponents())
	{
		std::cout << comp->GetMetaData().Save(comp, 0);
	}
	for (auto child : gameObject->transform->GetChildren())
	{
		std::cout << "child\n";
		SaveGameObjectAsPrefab(child->GetGameObject(), file);
		std::cout << "end\n";
	}
}

