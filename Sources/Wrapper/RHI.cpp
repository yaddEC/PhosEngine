// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>

#include "Resource/ShaderProgram.hpp"
#include "Resource/Texture.hpp"
#include "Resource/SubMesh.hpp"

#define RHI_EXPORTS
#include "Wrapper/RHI.hpp"

using namespace Wrapper;

GLFWwindow* RHI::InitWindow(int width, int height, const char* windowName)
{
	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "FAILED TO INITIALIZE GLFW" << std::endl;
		return nullptr;
	}

	GLFWwindow* window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
	if (!window)
	{
		std::cout << "FAILED TO CREATE A WINDOW" << std::endl;
		return nullptr;
	}
	SetCurrentContext(window);

	return window;
}

bool RHI::InitGlew()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return false;
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	return true;
}

bool RHI::WindowShouldClose(GLFWwindow* window)
{
	return glfwWindowShouldClose(window);
}

void RHI::SwapBuffer(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

Maths::Vec2 RHI::GetWindowSize(GLFWwindow* window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return Maths::Vec2(width, height);
}

void RHI::PollEvents()
{
	glfwPollEvents();
}

void RHI::DestroyWindow(GLFWwindow* window)
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* RHI::GetCurrentContext()
{
	return glfwGetCurrentContext();
}

void RHI::SetCurrentContext(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
}

void RHI::EnableCulling()
{
	glEnable(GL_CULL_FACE);
}

void RHI::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void RHI::BindTexture(unsigned int* textureKey, unsigned char* data, int channel, int width, int height)
{
	glGenTextures(1, textureKey);
	glBindTexture(GL_TEXTURE_2D, *textureKey);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		if (channel == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		if (channel == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		if (channel == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		if (channel == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void Wrapper::RHI::ResizeTexture(unsigned int* textureKey, int channel, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, *textureKey);

	if (channel == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	if (channel == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
}

void Wrapper::RHI::BindShader(unsigned int* programKey, std::vector<Resource::ShaderInfo> &shaderList)
{
	*programKey = glCreateProgram();

	for (auto& shader : shaderList)
	{
		shader.key = GetCompiledShader(shader.shaderType, shader.source);
		if (shader.key == -1)
		{
			std::cout << "Error binding shader" << std::endl;
			return;
		}
	}

	for (auto& shader : shaderList)
	{
		glAttachShader(*programKey, shader.key);
	}

	glLinkProgram(*programKey);

	int success;
	glGetProgramiv(*programKey, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(*programKey, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	for (auto& shader : shaderList)
	{
		glDeleteShader(shader.key);
	}
}

void Wrapper::RHI::UserProgram(unsigned int* programKey)
{
	glUseProgram(*programKey);
}

void Wrapper::RHI::ShaderMat(const unsigned int& programKey, const std::string& uniformName, const Maths::Mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(programKey, uniformName.c_str()), 1, true, &mat.data_4_4[0][0]);
}

void Wrapper::RHI::ShaderVec3(const unsigned int& programKey, const std::string& uniformName, const Maths::Vec3& vec3)
{
	glUniform3fv(glGetUniformLocation(programKey, uniformName.c_str()), 1, &vec3.x);
}

void Wrapper::RHI::ShaderInt(const unsigned int& programKey, const std::string& uniformName, int value)
{
	glUniform1i(glGetUniformLocation(programKey, uniformName.c_str()), value);
}

void Wrapper::RHI::UnloadShader(const unsigned int* programKey)
{
	glDeleteProgram(*programKey);
}

void Wrapper::RHI::ActivateTexture(const Resource::Texture& texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.GetTextureKey());
}

void Wrapper::RHI::RenderSubMesh(const unsigned int& VAO, const std::vector<unsigned int> indices)
{
	glBindVertexArray(VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Wrapper::RHI::SetSubMeshData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, const std::vector<Resource::Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Resource::Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Resource::Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Resource::Vertex), (void*)offsetof(Resource::Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Resource::Vertex), (void*)offsetof(Resource::Vertex, UVCoords));

	glBindVertexArray(0);
}

void Wrapper::RHI::UnloadSubMesh(const unsigned int& VAO, const unsigned int& VBO, const unsigned int& EBO)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

int Wrapper::RHI::GetCompiledShader(unsigned int shaderType, const std::string& shaderSource)
{
	//compile shader
	unsigned int shaderID = glCreateShader(shaderType);

	const char* source = shaderSource.c_str();
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);


	// check if shader compilation succeded
	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

		char* infoLog = new char[length];
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);

		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		delete[] infoLog;

		return -1;
	}

	return shaderID;
}
