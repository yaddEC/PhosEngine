#pragma once
#include <vector>
#include "Maths/Maths.hpp"
#include <string>
#include <functional>

#include "dllInclude.hpp"

namespace Engine
{
	class GameObject;

	class PHOSENGINE_API Transform
	{
	public:
		Transform(Maths::Vec3 _position = Maths::Vec3(),
			Maths::Quaternion _rotation = Maths::Quaternion(),
			Maths::Vec3 _scale = Maths::Vec3(1, 1, 1));

		Transform(const Transform& _transform)
			: position(_transform.position), rotation(_transform.rotation), scale(_transform.scale), rotationEuler(_transform.rotationEuler) {}

		Maths::Vec3 position;
		Maths::Quaternion rotation;
		Maths::Vec3 scale;
		Maths::Vec3 rotationEuler;

		void Destroy(bool destroyChildren = true);


		void AddChild(Transform* child);
		void SetParent(Transform* _parent);

		std::vector<Transform*> GetChildren() const { return m_children; }
		Transform* GetParent() { return m_parent; }

		Maths::Mat4 GetGlobalMatrix() const { return m_globalMatrix; }
		GameObject* GetGameObject() const { return m_gameObject; }
		void SetGameObject(GameObject* _gameobject) { m_gameObject = _gameobject; }

		void SetRotation(Maths::Vec3 rotation);

		void SetRotation(Maths::Quaternion quaternion);

		void AddRotation(Maths::Quaternion quaternion);

		Maths::Vec3 GetForwardVector();
		Maths::Vec3 GetUpVector();
		Maths::Vec3 GetRightVector();
		Maths::Vec3 GetGlobalPosition();

		void ComputeGlobalMatrix(const Maths::Mat4& parentMatrix = Maths::Mat4::CreateDiagonalMatrix(1)); // Recursive

		void OnGUI();

		typedef std::function<void()> TransformChangedCallback;

		void RegisterTransformChangedCallback(TransformChangedCallback callback);
	private:
		Maths::Mat4 m_globalMatrix;

		bool m_isDestroyed = false;

		Transform* m_parent = nullptr;
		std::vector<Transform*> m_children;
		GameObject* m_gameObject{nullptr};
		std::vector<TransformChangedCallback> m_transformChangedCallbacks;

		void RemoveChild(Transform* child);
	};
}
