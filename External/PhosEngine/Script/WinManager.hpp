#pragma once

#include "Engine/MonoBehaviour.hpp"

namespace Engine
{
	class GameObject;
}

namespace Script
{
	class PHOSENGINE_API WinManager : public Engine::MonoBehaviour
	{
	public:
		WinManager();
		~WinManager();
		void AddCount(bool isLeftSide);
		void ReduceCount(bool isLeftSide);
		void Update() override;
		void OnInspector() override;
		Reflection::ClassMetaData& GetMetaData() override;

	private:
		int m_leftCount;
		int m_rightCount;
	};


}