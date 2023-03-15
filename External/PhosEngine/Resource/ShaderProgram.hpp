#pragma once
#include <string>
#include <vector>
#include "Maths/Maths.hpp"
#include "IResource.hpp"

#ifdef SHADERPROGRAM_EXPORTS
#define SHADERPROGRAM_API __declspec(dllexport)
#else
#define SHADERPROGRAM_API __declspec(dllimport)
#endif

namespace Resource
{
	struct ShaderInfo
	{
		std::string source;
		unsigned int shaderType;
		unsigned int key;
	};


	class SHADERPROGRAM_API ShaderProgram : public IResource
	{
	public:

		ShaderProgram() : IResource() {};
		~ShaderProgram();

		void Load(const std::string& filepath) override;
		void Bind() override;

		void Unload() override;

		class Texture* GenerateFileIcon() override;

		void Use() const;

		void SetUniformMatrix(const std::string& uniformName, const Maths::Mat4& mat) const;
		void SetUniformVec3(const std::string& uniformName, const Maths::Vec3& vec3) const;
		void SetUniformInt(const std::string& uniformName, int value) const;


	private:
		unsigned int m_programKey;

		int GetCompiledShader(unsigned int shaderType, const std::string& shaderSource);

		std::vector<ShaderInfo> m_shaderList;
	};
}

