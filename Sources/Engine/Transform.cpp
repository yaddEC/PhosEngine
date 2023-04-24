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
Transform::Transform(Vec3 _position, Quaternion _rotation, Vec3 _scale)
	: position(_position), rotation(_rotation), scale(_scale) {}

void Transform::Destroy(bool destroyChildren)
{
	m_isDestroyed = true;

	if (m_parent) // delete self from parent if has one
		m_parent->RemoveChild(this);

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

void Engine::Transform::SetRotation(Maths::Vec3 rotation)
{
	this->rotation = this->rotation.ToQuaternion(rotation * DEG2RAD);
	rotationEuler = rotation;
}

void Engine::Transform::SetRotation(Maths::Quaternion quaternion)
{
	rotation = quaternion;
}

void Engine::Transform::AddRotation(Maths::Quaternion quaternion)
{
	rotation *= quaternion;
}


void Transform::ComputeGlobalMatrix(const Mat4& parentMatrix)
{
	Mat4 localMatrix = Quaternion::CreateTransformMatrix(position, rotation, scale);
	m_globalMatrix = localMatrix * parentMatrix;
	for (Transform* child : m_children)
		child->ComputeGlobalMatrix(m_globalMatrix);
}

void Transform::OnGUI()
{

	Vec3 tempRot = rotationEuler * Maths::RAD2DEG;
	Wrapper::GUI::EditVec3("Position", position, true, 0.05f);
	Wrapper::GUI::EditVec3("Rotation", tempRot, true, 0.1f);
	Wrapper::GUI::EditVec3("Scale", scale, true, 0.05f);
	Quaternion newQuat = this->rotation.ToQuaternion(tempRot * DEG2RAD);
	rotationEuler = tempRot * DEG2RAD;
	SetRotation(newQuat);
}

void Transform::SetParent(Transform* _parent)
{
	if (m_parent)
		m_parent->RemoveChild(this);
	m_parent = _parent;
	m_parent->AddChild(this);
}

void Engine::Transform::RemoveChild(Transform* child)
{
	m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
}

void Engine::Transform::AddChild(Transform* child)
{
	if (child->GetParent())
		child->GetParent()->RemoveChild(child);
	m_children.push_back(child);
	child->m_parent = this;
}

