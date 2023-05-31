#pragma once

#include "Reflection/ClassMetaData.hpp"

#include "dllInclude.hpp"

namespace Engine
{
	class GameObject;
	class Transform;

	class PHOSENGINE_API MonoBehaviour
	{
	public:

		MonoBehaviour(bool _renderingComponent = false, bool _overrideTransform = false);
		virtual ~MonoBehaviour();
		
		GameObject* gameobject;
		Transform* transform;

		bool isActive = true;

		virtual void Start() {};
		virtual void OnGizmo() {};
		virtual void OnTriggerEnter(GameObject* go) {};
		virtual void OnTriggerStay(GameObject* go) {};
		virtual void OnTriggerExit(GameObject* go) {};
		virtual void OnCollisionEnter(GameObject* go) {};
		virtual void OnCollisionStay(GameObject* go) {};
		virtual void OnCollisionExit(GameObject* go) {};
		virtual void Update() {};
		virtual void GUIUpdate() {};
		virtual void OnInspector();
		virtual void OnDestroy() {};
		const bool renderingComponent = false;
		const bool overrideTransform = false;
		virtual Reflection::ClassMetaData& GetMetaData() = 0;
	};
}