#pragma once

#ifdef MONOBEHAVIOUR_EXPORTS
#define MONOBEHAVIOUR_API __declspec(dllexport)
#else
#define MONOBEHAVIOUR_API __declspec(dllimport)
#endif

namespace Engine
{
	class GameObject;
	class Transform;

	class MONOBEHAVIOUR_API MonoBehaviour
	{
	public:
		
		GameObject* gameobject;
		Transform* transform;

		bool isActive = true;

		virtual void Start() {};
		virtual void Update() {};
		virtual void OnDestroy() {};
	};
}