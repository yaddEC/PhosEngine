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

		void SetTexture(const std::string& uniformName, int value, const Texture& texture) const;
	private:
		std::vector<ShaderInfo> m_postProShaderList;
		unsigned int m_progKey;
	};
}