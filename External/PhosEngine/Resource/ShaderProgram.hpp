#pragma once
#include <string>
#include <vector>
#include "Maths/Maths.hpp"
#include "IResource.hpp"

#include "dllInclude.hpp"

namespace Resource
{
	class CubeMap;
	class Texture;

	struct ShaderInfo
	{
		std::string source;
		unsigned int shaderType;
		unsigned int key;
	};

	class PHOSENGINE_API ShaderProgram : public IResource
	{
	public:

		ShaderProgram() : IResource() {};
		~ShaderProgram();

		void Load(const std::string& filepath) override;
		void Bind() override;

		void Unload() override;
		std::string GetTypeName() { return "ShaderProgram"; }

		Texture* GenerateFileIcon() override;

		void Use();

		void SetUniformMatrix(const std::string& uniformName, const Maths::Mat4& mat) const;
		void SetUniformVec3(const std::string& uniformName, const Maths::Vec3& vec3) const;
		void SetUniformVec4(const std::string& uniformName, const Maths::Vec4& vec4) const;
		void SetUniformInt(const std::string& uniformName, int value) const;
		void SetUniformBool(const std::string& uniformName, bool value) const;
		void SetUniformFloat(const std::string& uniformName, float value) const;
		void SetTexture(const std::string& uniformName, int value, const Texture& texture) const;
		void SetCubeMap(const std::string& uniformName, int value, const CubeMap& texture) const;

	private:
		unsigned int m_programKey;

		std::vector<ShaderInfo> m_shaderList;
	};
}

