#pragma once
#include <string>
#include <vector>
#include <map>
#include "Maths/Maths.hpp"
#include "IResource.hpp"
#include "Resource/ShaderInfo.hpp"

#include "dllInclude.hpp"

namespace Resource
{
	class CubeMap;
	class Texture;

	class PHOSENGINE_API ShaderProgram : public IResource
	{
	public:

		ShaderProgram() : IResource() {};
		~ShaderProgram();

		void Load() override;
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

		void SetUniformMatrixArray(const std::string& uniformName,
			const std::vector<Maths::Mat4> matrices);
		void SetUniformMatrixArray(const std::string& uniformName,
			const std::map<std::string, Maths::Mat4> matrices);

	private:
		unsigned int m_programKey;

		std::vector<ShaderInfo> m_shaderList;
	};
}

