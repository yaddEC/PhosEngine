#pragma once
#include "Resource/IResource.hpp"
#include "Resource/ShaderInfo.hpp"

namespace Resource 
{
	class PostProcessingShader : public IResource
	{
	public:
		PostProcessingShader();
		~PostProcessingShader();
		void Load(const std::string& filepath) override;
		void Bind() override;
		void Unload() override;
		class Texture* GenerateFileIcon() override { return nullptr; };

		void Use();

	private:
		std::vector<ShaderInfo> m_postProShaderList;
		unsigned int m_progKey;
	};
}