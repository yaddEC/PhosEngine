#pragma once

#include "Engine/MonoBehaviour.hpp"

namespace Engine
{
	class GameObject;
}

namespace Script
{
	class PHOSENGINE_API OutOfBound : public Engine::MonoBehaviour
	{
	public:
		OutOfBound();
		~OutOfBound();
		void Start() override;
		void OnInspector() override;
		Reflection::ClassMetaData& GetMetaData() override;

		Maths::Vec3 GetInitPos() const { return m_initPos; }
	private:
		Maths::Vec3 m_initPos;
	};


}