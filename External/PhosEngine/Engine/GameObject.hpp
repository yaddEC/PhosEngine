#pragma once
#include <vector>
#include <string>
#include <typeindex>
#include "Maths/Maths.hpp"

#ifdef GAMEOBJECT_EXPORTS
#define GAMEOBJECT_API __declspec(dllexport)
#else
#define GAMEOBJECT_API __declspec(dllimport)
#endif

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

	class GAMEOBJECT_API GameObject
	{
	public:

		GameObject();

		std::string name;

		Transform* transform;

		void Start();
		void Update(); 
		void OnDestroy();

		Scene* GetScene() { return scene; }
		void SetScene(Scene* _scene) { scene = _scene; }
		std::vector<MonoBehaviour*> GetComponents() { return components; }

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

	private:
		std::vector<MonoBehaviour*> components;
		std::vector<MonoBehaviour*> componentsBuffer;
		Scene* scene = nullptr;


	};
}