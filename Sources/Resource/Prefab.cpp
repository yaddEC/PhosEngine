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

#include "Resource/Prefab.hpp"


using namespace Resource;

void Resource::Prefab::Load()
{
	m_gameObjectList.clear();
	std::vector<std::string> fileData = Parser::ConvertFileToStringArray(GetFilePath());
	size_t lineIndex = 0;
	ParseGameObject(fileData, lineIndex);
}

void Resource::Prefab::Bind()
{

}

void Resource::Prefab::Unload()
{
	for (Engine::GameObject* go : m_gameObjectList)
	{
		delete go;
	}
	m_gameObjectList.clear();
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

std::vector<Engine::GameObject*> Resource::Prefab::GetCopy() const
{
	using namespace Engine;

	std::vector<GameObject*> result;
	for (GameObject* go : m_gameObjectList)
	{
		GameObject* newGameObject = new GameObject();
		newGameObject->name = go->name;
		newGameObject->SetID(go->GetID());
		result.push_back(newGameObject);
		
	}

	for (size_t i = 0; i < result.size(); i++)
	{
		result[i]->transform->position = m_gameObjectList[i]->transform->position;
		result[i]->transform->rotation = m_gameObjectList[i]->transform->rotation;
		result[i]->transform->scale = m_gameObjectList[i]->transform->scale;

		for (auto child : m_gameObjectList[i]->transform->GetChildren())
		{
			for (GameObject* go : result)
			{
				if (go->GetID() == child->GetGameObject()->GetID())
				{
					result[i]->transform->AddChild(go->transform);
				}
			}
		}

		for (auto comp : m_gameObjectList[i]->GetComponentBuffer())
		{
			// TODO PROPER COPY
			Engine::MonoBehaviour* newComp = Reflection::ClassMetaData::AddComponent(comp->GetMetaData().name, result[i]);
			newComp->GetMetaData().Copy(comp, newComp);
		}
	}

	return result;
}

Engine::GameObject* Resource::Prefab::ParseGameObject(const std::vector<std::string>& fileData, size_t& lineIndex)
{
	using namespace Engine;
	GameObject* newGameObject = new GameObject();
	m_gameObjectList.push_back(newGameObject);
	for (; lineIndex < fileData.size(); lineIndex++)
	{
		std::vector<std::string> tokens = Parser::Tokenize(fileData[lineIndex], ' ', '\t');
		
		if (tokens[0] == "name")
		{
			newGameObject->name = tokens[1];
		}
		else if (tokens[0] == "id")
		{
			newGameObject->SetID(static_cast<unsigned int>(std::stof(tokens[1])));
		}
		else if (tokens[0] == "transform")
		{
			newGameObject->transform->position = Maths::Vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
			newGameObject->transform->rotationEuler = Maths::Vec3(std::stof(tokens[4]), std::stof(tokens[5]), std::stof(tokens[6]));
			newGameObject->transform->scale = Maths::Vec3(std::stof(tokens[7]), std::stof(tokens[8]), std::stof(tokens[9]));
		}
		else if (tokens[0] == "component")
		{
			Engine::MonoBehaviour* comp = Reflection::ClassMetaData::AddComponent(tokens[1], newGameObject);
			if(comp)
				comp->GetMetaData().Parse(fileData, ++lineIndex, comp);
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
	return nullptr;
}



void Resource::Prefab::SaveGameObjectAsPrefab(Engine::GameObject* gameObject, std::fstream& file, int depth)
{

	std::string tab = std::string(depth, '\t');
	Maths::Vec3 transformRot = gameObject->transform->rotation.ToEulerAngles();
	file << tab << "name \"" << gameObject->name << "\"\n"
		<< tab << "id " << gameObject->GetID() << '\n'
		<< tab << "transform " << gameObject->transform->position.x << ' ' << gameObject->transform->position.y << ' ' << gameObject->transform->position.z 
		<< ' ' << gameObject->transform->rotationEuler.x << ' ' << gameObject->transform->rotationEuler.y << ' ' << gameObject->transform->rotationEuler.z
		<< ' ' << gameObject->transform->scale.x << ' ' << gameObject->transform->scale.y << ' ' << gameObject->transform->scale.z << '\n';
	for (auto comp : gameObject->GetComponents())
	{
		file << comp->GetMetaData().Save(comp, depth + 1);
	}
	for (auto child : gameObject->transform->GetChildren())
	{
		file << tab << "child\n";
		SaveGameObjectAsPrefab(child->GetGameObject(), file, depth + 1);
	}
	file << tab << "end\n";

	
}

