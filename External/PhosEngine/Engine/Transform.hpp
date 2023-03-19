#pragma once
#include <vector>
#include "Maths/Maths.hpp"

#ifdef TRANSFORM_EXPORTS
#define TRANSFORM_API __declspec(dllexport)
#else
#define TRANSFORM_API __declspec(dllimport)
#endif

namespace Engine
{
	class GameObject;

	class TRANSFORM_API Transform
	{
	public:
		Transform(Maths::Vec3 _position = Maths::Vec3(),
			Maths::Vec3 _rotation = Maths::Vec3(),
			Maths::Vec3 _scale = Maths::Vec3(1, 1, 1));

		Maths::Vec3 position;
		Maths::Vec3 rotation;
		Maths::Vec3 scale;

		void Destroy(bool destroyChildren = true);


		void AddChild(Transform* child) { m_children.push_back(child); child->m_parent = this; }
		std::vector<Transform*> GetChildren() const { return m_children; }

		Maths::Mat4 GetGlobalMatrix() const { return m_globalMatrix; }

		void ComputeGlobalMatrix(const Maths::Mat4& parentMatrix = Maths::Mat4::CreateDiagonalMatrix(1)); // Recursive

		void OnGUI();

	private:
		Maths::Mat4 m_globalMatrix;

		bool m_isDestroyed = false;

		Transform* m_parent = nullptr;
		std::vector<Transform*> m_children;

		GameObject* gameObject;
	};
}

