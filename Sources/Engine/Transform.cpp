// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Wrapper/GUI.hpp"
#include "Engine/GameObject.hpp"
#include "Resource/Parser.hpp"

#define TRANSFORM_EXPORTS
#include "Engine/Transform.hpp"

using namespace Maths;
using namespace Engine;


// Initializer
Transform::Transform(Vec3 _position, Vec3 _rotation, Vec3 _scale)
	: position(_position), rotation(_rotation), scale(_scale) {}

void Transform::Destroy(bool destroyChildren)
{
	m_isDestroyed = true;

	if (m_parent) // delete self from parent if has one
		m_parent->m_children.erase(std::remove(m_parent->m_children.begin(), m_parent->m_children.end(), this), m_parent->m_children.end());

	if (destroyChildren)
	{
		for (Transform* child : m_children)
		{
			child->gameObject->Destroy();
		}
	}
	else
	{
		for (Transform* child : m_children)
		{
			child->m_parent = this->m_parent;
		}
	}
}

void Transform::ComputeGlobalMatrix(const Mat4& parentMatrix)
{
	Mat4 localMatrix = Mat4::CreateTransformMatrix(position, rotation, scale);
	m_globalMatrix = localMatrix * parentMatrix;
	for (Transform* child : m_children)
		child->ComputeGlobalMatrix(m_globalMatrix);
}

void Transform::OnGUI()
{
	Wrapper::GUI::EditVec3("Position", position, 0.05f);
	Wrapper::GUI::EditVec3("Rotation", rotation, 0.01f);
	Wrapper::GUI::EditVec3("Scale", scale, 0.05f);
}

void Engine::Transform::Parse(const std::vector<std::string>& fileData, size_t& lineIndex)
{
	for (; lineIndex < fileData.size(); lineIndex++)
	{
		std::vector<std::string> tokens = Resource::Parser::Tokenize(fileData[lineIndex], ' ', '\t');

		if (tokens[0] == "pos")
		{
			position = Maths::Vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
		}
		else if (tokens[0] == "rot")
		{
			rotation = Maths::Vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
		}
		else if (tokens[0] == "scale")
		{
			scale = Maths::Vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
		}
		else if (tokens[0] == "end")
		{
			return;
		}
	}
}
