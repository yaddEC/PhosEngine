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

		MonoBehaviour(bool _renderingComponent = false);
		virtual ~MonoBehaviour();
		
		GameObject* gameobject;
		Transform* transform;

		bool isActive = true;

		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void GUIUpdate() = 0;
		virtual void OnDestroy() = 0;
		const bool renderingComponent = false;

		virtual Reflection::ClassMetaData& GetMetaData() = 0;
	};
}