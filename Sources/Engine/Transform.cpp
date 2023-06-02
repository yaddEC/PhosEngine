// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Wrapper/GUI.hpp"
#include "Wrapper/PhysicsWrapper.hpp"
#include "Engine/GameObject.hpp"
#include "Resource/Parser.hpp"

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

void Engine::Transform::RotateX(float angle)
{
	rotationEuler.x += angle;
	rotation = Quaternion::ToQuaternion(rotationEuler);
}

void Engine::Transform::RotateY(float angle)
{
	rotationEuler.y += angle;
	rotation = Quaternion::ToQuaternion(rotationEuler);
}

void Engine::Transform::RotateZ(float angle)
{
	rotationEuler.z += angle;
	rotation = Quaternion::ToQuaternion(rotationEuler);
}

void Engine::Transform::AddRotation(Maths::Quaternion quaternion)
{
	rotation *= quaternion;
}

Vec3 Engine::Transform::GetForwardVector()
{
	Vec4 forwardVector4 = m_globalMatrix * Vec4(0,0,1,0);
	Vec3 forwardVector3 = Vec3(forwardVector4.x, forwardVector4.y, forwardVector4.z);
	forwardVector3.Normalize();
	return forwardVector3;
}

Vec3 Engine::Transform::GetUpVector()
{
	Vec4 upVector4 = m_globalMatrix * Vec4(0, 1, 0, 0);
	Vec3 upVector3 = Vec3(upVector4.x, upVector4.y, upVector4.z);
	upVector3.Normalize();
	return upVector3;
}

Maths::Vec3 Engine::Transform::GetRightVector()
{
	Vec4 RightdVector4 = m_globalMatrix * Vec4(1, 0, 0, 0);
	Vec3 RightVector3 = Vec3(RightdVector4.x, RightdVector4.y, RightdVector4.z);
	RightVector3.Normalize();
	return RightVector3;
}

Maths::Vec3 Engine::Transform::GetGlobalPosition()
{
	//return (m_globalMatrix * Maths::Vec4(position.x, position.y, position.z, 1)).xyz();
	return Maths::Vec3(m_globalMatrix.data_4_4[0][3], m_globalMatrix.data_4_4[1][3], m_globalMatrix.data_4_4[2][3]);
}


void Transform::ComputeGlobalMatrix(const Mat4& parentMatrix)
{
	if (m_isTransformOverride)
	{
		m_globalMatrix = Quaternion::CreateTransformMatrix(position, rotation, scale);
		for (Transform* child : m_children)
			child->ComputeGlobalMatrix(m_globalMatrix);
	}
	else
	{
		Mat4 localMatrix = Quaternion::CreateTransformMatrix(position, rotation, scale);
		m_globalMatrix = localMatrix * parentMatrix;
		for (Transform* child : m_children)
			child->ComputeGlobalMatrix(m_globalMatrix);
	}
	
}

void Transform::OnGUI()
{
	Vec3 tempRot = rotationEuler * Maths::RAD2DEG;
	bool positionChanged = Wrapper::GUI::EditVec3("Position", position, true, 0.05f);
	bool rotChange = Wrapper::GUI::EditVec3("Rotation", tempRot, true, 0.1f);
	bool scaleChanged = Wrapper::GUI::EditVec3("Scale", scale, true, 0.05f);

	if (rotChange)
	{
		Quaternion newQuat = this->rotation.ToQuaternion(tempRot * DEG2RAD);
		rotationEuler = tempRot * DEG2RAD;
		SetRotation(newQuat);
	}

	if (positionChanged || rotChange || scaleChanged)
	{
		for (auto& callback : transformChangedCallbacks)
		{
			callback();
		}
	}
}

void Engine::Transform::RegisterTransformChangedCallback(TransformChangedCallback callback)
{
	transformChangedCallbacks.push_back(callback);
}

void Engine::Transform::BeginOverride()
{
	m_isTransformOverride = true;
	Maths::Mat4 transformMatrix = GetGlobalMatrix();

	// Set all to global
	/*position = GetGlobalPosition();
	rotationEuler = (transformMatrix * Maths::Vec4(rotationEuler, 0.f)).xyz();
	scale.x = Maths::Vec3(transformMatrix.data4V[0].x, transformMatrix.data4V[1].x, transformMatrix.data4V[2].x).GetMagnitude();
	scale.y = Maths::Vec3(transformMatrix.data4V[0].y, transformMatrix.data4V[1].y, transformMatrix.data4V[2].y).GetMagnitude();
	scale.z = Maths::Vec3(transformMatrix.data4V[0].z, transformMatrix.data4V[1].z, transformMatrix.data4V[2].z).GetMagnitude();
	rotation = Quaternion::ToQuaternion(rotationEuler);*/
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

