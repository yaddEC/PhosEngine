#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include "Maths/Maths.hpp"

#ifdef RHI_EXPORTS
#define RHI_API __declspec(dllexport)
#else
#define RHI_API __declspec(dllimport)
#endif

namespace Resource 
{
	class Texture;
	struct Vertex;
	struct ShaderInfo;
}
namespace Wrapper 
{
	class RHI_API RHI
	{
	public:
		static GLFWwindow* InitWindow(int width, int height, const char* windowName);
		static bool  InitGlew();

		static bool WindowShouldClose(GLFWwindow* window);
		static void SwapBuffer(GLFWwindow* window);
		static void PollEvents();

		static Maths::Vec2 GetWindowSize(GLFWwindow* window);

		static void DestroyWindow(GLFWwindow* window);

		static GLFWwindow* GetCurrentContext();
		static void SetCurrentContext(GLFWwindow* window);

		static void EnableCulling(); // TEMP
		static void EnableDepthTest(); // TEMP

		//Resource
		static void BindTexture(unsigned int* textureKey, unsigned char* data, int channel, int width, int height);
		static void ResizeTexture(unsigned int* textureKey, int channel, int width, int height);

		static void BindShader(unsigned int* programKey, std::vector<Resource::ShaderInfo> &shaderList);
		static void UserProgram(unsigned int* programKey);
		static void ShaderMat(const unsigned int& programKey, const std::string& uniformName, const Maths::Mat4& mat);
		static void ShaderVec3(const unsigned int& programKey, const std::string& uniformName, const Maths::Vec3& vec3);
		static void ShaderInt(const unsigned int& programKey, const std::string& uniformName, int value);
		static void UnloadShader(const unsigned int* programKey);

		static void ActivateTexture(const Resource::Texture& texture);
		static void RenderSubMesh(const unsigned int& VAO, std::vector<unsigned int> indices);
		static void SetSubMeshData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, const std::vector<Resource::Vertex> &vertices, const std::vector<unsigned int> &indices);
		static void UnloadSubMesh(const unsigned int& VAO, const unsigned int& VBO, const unsigned int& EBO);
	private:
		static int GetCompiledShader(unsigned int shaderType, const std::string& shaderSource);
	};
}