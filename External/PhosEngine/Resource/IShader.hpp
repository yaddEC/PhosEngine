#pragma once
#include "Resource/IResource.hpp"
#include "Maths/Maths.hpp"
#include <string>

#include "dllInclude.hpp"

namespace Resource
{
	class PHOSENGINE_API IShader : public IResource
	{
	public:

		IShader() : IResource() {}


		void Load() override;
		void Unload() override;
		void GUIUpdate() override;

		unsigned int GetShaderKey() const { return p_shaderKey; }
		std::string GetSourceCode() const { return p_sourceCode; }
		bool GenerationIgnore() const { return p_ignoreGeneration; }

	protected:
		std::string p_sourceCode;
		unsigned int p_shaderKey = 0;
		bool p_ignoreGeneration = false;
	};


	class PHOSENGINE_API VertexShader : public IShader
	{
	public:
		void Bind() override;
		std::string GetTypeName() { return "Vertex Shader"; }
	};


	class PHOSENGINE_API FragmentShader : public IShader
	{
	public:
		void Bind() override;
		std::string GetTypeName() { return "Fragment Shader"; }
	};
}