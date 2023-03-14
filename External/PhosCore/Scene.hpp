#pragma once
#include <vector>
#include <string>
#include "Maths.hpp"

#ifdef SCENE_EXPORTS
#define SCENE_API __declspec(dllexport)
#else
#define SCENE_API __declspec(dllimport)
#endif


namespace LowRenderer
{
	class MeshRenderer;
}



namespace Engine
{
	class SCENE_API Scene
	{
	public:

		Scene();

		void Update();

		inline std::vector<LowRenderer::MeshRenderer*> GetModelList() { return modelList; }
		inline void AddModel(LowRenderer::MeshRenderer* model) { modelList.push_back(model); }


	private:
		std::vector<LowRenderer::MeshRenderer*> modelList;

	};
}

