#pragma once
#include <vector>
#include <string>
#include "Maths/Maths.hpp"

#ifdef GAMEOBJECT_EXPORTS
#define GAMEOBJECT_API __declspec(dllexport)
#else
#define GAMEOBJECT_API __declspec(dllimport)
#endif

namespace Engine
{
	class Transform;
	class MonoBehaviour;
	class Scene;

	class GAMEOBJECT_API GameObject
	{
	public:

		GameObject(Scene* _scene, Transform* _transform);

		std::string name;

		Transform* transform;

		void Start();
		void Update(); 
		void OnDestroy();

		Scene* GetScene() { return scene; }
		std::vector<MonoBehaviour*> GetComponents() { return components; }

	private:
		std::vector<MonoBehaviour*> components;
		Scene* scene;

	};
}