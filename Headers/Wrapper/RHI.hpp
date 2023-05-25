#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <array>

#include "Maths/Maths.hpp"

#include "dllInclude.hpp"

namespace Resource 
{
	class Texture;
	class CubeMap;
	struct Vertex;
	struct SkinnedVertex;
	struct ShaderInfo;
}


namespace Wrapper 
{
	class PHOSENGINE_API RHI
	{
	public:

		static void EnableCulling(); // TEMP
		static void EnableDepthTest(); // TEMP

		//Resource
		static void BindTexture(unsigned int* textureKey, unsigned char* data, int channel, int width, int height);
		static void BindDepthTexture(unsigned int* textureKey, int width, int height);
		static void ResizeTexture(unsigned int* textureKey, int channel, int width, int height);

		static void BindShader(unsigned int* shaderKey, const std::string& sourceCode, unsigned int ShaderType);
		static void BindShader(unsigned int* programKey, std::vector<Resource::ShaderInfo> &shaderList);
		static void UseProgram(unsigned int* programKey);
		static void ShaderMat(const unsigned int& programKey, const std::string& uniformName, const Maths::Mat4& mat);
		static void ShaderMatList(const unsigned int& programKey, const std::string& uniformName, const std::vector<Maths::Mat4>& matList);
		static void ShaderVec3(const unsigned int& programKey, const std::string& uniformName, const Maths::Vec3& vec3);
		static void ShaderVec4(const unsigned int& programKey, const std::string& uniformName, const Maths::Vec4& vec4);
		static void ShaderInt(const unsigned int& programKey, const std::string& uniformName, int value);
		static void ShaderFloat(unsigned int programKey, const std::string& uniformName, float value);
		static void UnloadShaderProgram(const unsigned int* programKey);
		static void UnloadShader(const unsigned int* shaderKey);

		static void ActivateTexture(const Resource::Texture& texture, int value);
		static void ActivateCubeMap(const Resource::CubeMap& texture, int value);
		static void RenderSubMesh(const unsigned int& VAO, std::vector<unsigned int> indices);
		static void SetSubMeshData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO,
			const std::vector<Resource::Vertex> &vertices, const std::vector<unsigned int> &indices);
		static void SetSubMeshData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO,
			const std::vector<Resource::SkinnedVertex>& skinnedVertices, const std::vector<unsigned int>& indices);
		static void UnloadSubMesh(const unsigned int& VAO, const unsigned int& VBO, const unsigned int& EBO);

		static void CreateFrameBuffer(unsigned int* frameBufferKey, unsigned int* renderBufferKey, bool useRenderBuffer = true);
		static void BindFrameBuffer(unsigned int frameBufferKey, unsigned int renderBufferKey, int width, int height, bool updateize = false, bool useRenderBuffer = true);
		static void UnbindFrameBuffer();
		static void ClearFrameBuffer(const Maths::Vec4& clearColor, bool onlyDepth = false);
		static void AttachTextureToFrameBuffer(unsigned int textureKey, unsigned int frameBufferKey, bool useDepth = false);
		static void DetachTextureToFrameBuffer(unsigned int frameBufferKey, bool useDepth = false);
		static void UnloadFrameBuffer(unsigned int* frameBufferKey, unsigned int* renderBufferKey);

		static void BindCubeMap(unsigned int* cubeMapKey, unsigned char* data[], Resource::Texture* faces[]);
		static void UnloadCubeMap(const unsigned int* cubeMapKey);

		static std::array<char, 4> GetPixelColor(Maths::Vec2 viewportSize, Maths::Vec2 TabPos);

	private:
		static int GetCompiledShader(unsigned int shaderType, const std::string& shaderSource);
	};
}