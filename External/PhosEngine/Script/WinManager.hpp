#pragma once

#include <vector>
#include "Engine/MonoBehaviour.hpp"
#include "LowRenderer/CameraComponent.hpp"

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
		void Start() override;
		void AddCount(bool isLeftSide);
		void ReduceCount(bool isLeftSide);
		void Update() override;
		void OnInspector() override;
		Reflection::ClassMetaData& GetMetaData() override;

	private:
		//std::vector<LowRenderer::CameraComponent> allCam;
		int m_leftCount;
		int m_rightCount;
	};


}