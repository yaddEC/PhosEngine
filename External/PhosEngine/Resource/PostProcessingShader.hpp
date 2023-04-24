#pragma once
#include "Resource/IResource.hpp"

namespace Resource 
{
	struct PostProInfo
	{
		std::string fragSource;
		unsigned int key;
	};

	class PostProcessingShader : public IResource
	{
	public:
		PostProcessingShader();
		~PostProcessingShader();
		void Load(const std::string& filepath) override;
		void Bind() override;
		void Unload() override;
		void Save() override;
		void GUIUpdate() override;
		class Texture* GenerateFileIcon() override { return nullptr; };

	private:
		PostProInfo shaderInfo;
		
	};
}