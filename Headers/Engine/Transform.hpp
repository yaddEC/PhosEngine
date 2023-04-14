#pragma once
#include <vector>
#include "Maths/Maths.hpp"
#include <string>

#include "dllInclude.hpp"

namespace Engine
{
	class GameObject;

	class PHOSENGINE_API Transform
	{
	public:
		Transform(Maths::Vec3 _position = Maths::Vec3(),
			Maths::Vec3 _rotation = Maths::Vec3(),
			Maths::Vec3 _scale = Maths::Vec3(1, 1, 1));

		Maths::Vec3 position;
		Maths::Vec3 rotation;
		Maths::Vec3 scale;

		void Destroy(bool destroyChildren = true);


		void AddChild(Transform* child); 
		void SetParent(Transform* _parent); 

		std::vector<Transform*> GetChildren() const { return m_children; }
		Transform* GetParent() { return m_parent; }
		// child duplication is possible

		Maths::Mat4 GetGlobalMatrix() const { return m_globalMatrix; }
		GameObject* GetGameObject() const { return gameObject; }
		void SetGameObject(GameObject* _gameobject) { gameObject = _gameobject; }

		void ComputeGlobalMatrix(const Maths::Mat4& parentMatrix = Maths::Mat4::CreateDiagonalMatrix(1)); // Recursive

		void OnGUI();

		void Parse(const std::vector<std::string>& fileData, size_t& lineIndex);

	private:
		Maths::Mat4 m_globalMatrix;

		bool m_isDestroyed = false;

		Transform* m_parent = nullptr;
		std::vector<Transform*> m_children;
		GameObject* gameObject;

		void RemoveChild(Transform* child); 
	};
}

