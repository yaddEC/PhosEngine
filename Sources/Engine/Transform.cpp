// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------


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
			child->Destroy();
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
	/*if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::DragFloat3("Position", &position.x, 0.1f, -100, 100);
		ImGui::DragFloat3("Rotation", &rotation.x, 0.1f, -180, 180);
		ImGui::DragFloat3("Scale", &scale.x, 0.1f, -100, 100);
	}*/
}
