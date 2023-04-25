#pragma once
#include <vector>
#include <string>
#include <typeindex>
#include "Maths/Maths.hpp"

#include "dllInclude.hpp"

namespace LowRenderer
{
	class DirectionalLight;
	class PointLight;
	class SpotLight;
}

namespace Engine
{
	class Transform;
	class MonoBehaviour;
	class Scene;

	class PHOSENGINE_API GameObject
	{
	public:

		GameObject();

		std::string name;

		Transform* transform;

		void Start();
		void Update(); 
		void Destroy();
		void OnCollisionEnter(GameObject* gameobject);
		void OnCollisionStay(GameObject* gameobject);
		void OnCollisionExit(GameObject* gameobject);
		void OnTriggerEnter(GameObject* gameobject);
		void OnTriggerStay(GameObject* gameobject);
		void OnTriggerExit(GameObject* gameobject);

		Scene* GetScene() { return scene; }
		void SetScene(Scene* _scene) { scene = _scene; }
		std::vector<MonoBehaviour*> GetComponents() { return components; }
		std::vector<MonoBehaviour*> GetComponentBuffer() { return componentsBuffer; }

		template <typename T>
		T* AddComponent()
		{
			T* newComponent = new T();
			newComponent->gameobject = this;
			newComponent->transform = transform;
			componentsBuffer.push_back(newComponent);
			return newComponent;
		}

		template <class T>
		inline T* GetComponent(unsigned int index = 0)
		{
			T* res = nullptr;
			for (MonoBehaviour* component : components)
			{
				if (std::type_index(typeid(*component)) == std::type_index(typeid(T)))
				{
					res = (T*)component;
					if (index == 0)
						return res;
					else
						index--;
				}
			}
			return res;
		}

		template <class T>
		T* GetComponentInChildren(unsigned int index = 0);

		unsigned int GetID() { return m_ID; }
		void SetID(unsigned int id) { m_ID = id; }

	private:
		std::vector<MonoBehaviour*> components;
		std::vector<MonoBehaviour*> componentsBuffer;
		Scene* scene = nullptr;

		unsigned int m_ID;

	};
}