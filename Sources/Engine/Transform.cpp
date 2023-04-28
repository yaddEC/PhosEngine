// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Wrapper/GUI.hpp"
#include "Wrapper/PhysicsWrapper.hpp"
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
			child->m_gameObject->Destroy();
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

void Engine::Transform::SetRotation(Maths::Vec3 _rotation)
{
	rotation = rotation.ToQuaternion(_rotation);
	rotationEuler = _rotation;
}

void Engine::Transform::SetRotation(Maths::Quaternion quaternion)
{
	rotation = quaternion;
}

void Engine::Transform::AddRotation(Maths::Quaternion quaternion)
{
	rotation *= quaternion;
}

Vec3 Engine::Transform::GetForwardVector()
{
	Vec3 unitVector = Wrapper::GetUnitVectors();
	Vec4 forwardVector4 = m_globalMatrix * Vec4(0,0,unitVector.z,0);
	Vec3 forwardVector3 = Vec3(forwardVector4.x, forwardVector4.y, forwardVector4.z);
	forwardVector3.Normalize();
	return forwardVector3;
}

Vec3 Engine::Transform::GetUpVector()
{
	Vec3 unitVector = Wrapper::GetUnitVectors();
	Vec4 upVector4 = m_globalMatrix * Vec4(0, unitVector.y, 0, 0);
	Vec3 upVector3 = Vec3(upVector4.x, upVector4.y, upVector4.z);
	upVector3.Normalize();
	return upVector3;
}

Maths::Vec3 Engine::Transform::GetRightVector()
{
	Vec3 unitVector = Wrapper::GetUnitVectors();
	Vec4 RightdVector4 = m_globalMatrix * Vec4(unitVector.x, 0, 0, 0);
	Vec3 RightVector3 = Vec3(RightdVector4.x, RightdVector4.y, RightdVector4.z);
	RightVector3.Normalize();
	return RightVector3;
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
	bool rotChange = Wrapper::GUI::EditVec3("Rotation", tempRot, true, 0.1f);
	Wrapper::GUI::EditVec3("Scale", scale, true, 0.05f);

	if (rotChange)
	{
		Quaternion newQuat = this->rotation.ToQuaternion(tempRot * DEG2RAD);
		rotationEuler = tempRot * DEG2RAD;
		SetRotation(newQuat);
	}
	
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

