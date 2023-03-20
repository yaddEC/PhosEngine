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

		MonoBehaviour(bool _renderingComponent = false);
		virtual ~MonoBehaviour();
		
		GameObject* gameobject;
		Transform* transform;

		bool isActive = true;

		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void OnDestroy() = 0;

		const bool renderingComponent = false;
	};
}