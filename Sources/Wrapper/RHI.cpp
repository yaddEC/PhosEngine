// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>

#include "Resource/ShaderProgram.hpp"
#include "Resource/Texture.hpp"
#include "Resource/SubMesh.hpp"
#include "Resource/CubeMap.hpp"

#include "Engine/Input.hpp"
#include "Wrapper/Window.hpp"
#include "Wrapper/RHI.hpp"

using namespace Wrapper;


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


	if (data)
	{
		if (channel == 1)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);

		if (channel == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		if (channel == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		if (channel == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		if (channel == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

}

void Wrapper::RHI::BindDepthTexture(unsigned int* textureKey, int width, int height)
{
	glGenTextures(1, textureKey);
	glBindTexture(GL_TEXTURE_2D, *textureKey);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	float clampColor[4] = { 1, 1, 1, 1 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);
}

void Wrapper::RHI::ResizeTexture(unsigned int* textureKey, int channel, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, *textureKey);

	if (channel == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	if (channel == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

}

void Wrapper::RHI::BindShader(unsigned int* shaderKey, const std::string& sourceCode, unsigned int ShaderType)
{
	*shaderKey = GetCompiledShader(ShaderType, sourceCode.c_str());
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
			std::cout << shader.filePath << std::endl;
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
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED : " << shaderList[1] .filePath << "\n" << infoLog << std::endl;
	}

	// DELETE
	for (auto& shader : shaderList)
	{
		glDeleteShader(shader.key);
	}
}

void Wrapper::RHI::UseProgram(unsigned int* programKey)
{
	glUseProgram(*programKey);
}

void Wrapper::RHI::ShaderMat(const unsigned int& programKey, const std::string& uniformName, const Maths::Mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(programKey, uniformName.c_str()), 1, true, &mat.data_4_4[0][0]);
}

void Wrapper::RHI::ShaderMatList(const unsigned int& programKey, const std::string& uniformName, const std::vector<Maths::Mat4>& matList)
{
	glUniformMatrix4fv(glGetUniformLocation(programKey, uniformName.c_str()), static_cast<int>(matList.size()), true, &matList.at(0).data[0]);
}

void Wrapper::RHI::ShaderVec3(const unsigned int& programKey, const std::string& uniformName, const Maths::Vec3& vec3)
{
	glUniform3fv(glGetUniformLocation(programKey, uniformName.c_str()), 1, &vec3.x);
}

void Wrapper::RHI::ShaderVec4(const unsigned int& programKey, const std::string& uniformName, const Maths::Vec4& vec4)
{
	glUniform4fv(glGetUniformLocation(programKey, uniformName.c_str()), 1, &vec4.x);
}

void Wrapper::RHI::ShaderInt(const unsigned int& programKey, const std::string& uniformName, int value)
{
	glUniform1i(glGetUniformLocation(programKey, uniformName.c_str()), value);
}

void Wrapper::RHI::ShaderFloat(unsigned int programKey, const std::string& uniformName, float value)
{
	glUniform1f(glGetUniformLocation(programKey, uniformName.c_str()), value);
}

void Wrapper::RHI::UnloadShader(const unsigned int* shaderKey)
{
	glDeleteShader(*shaderKey);
}

void Wrapper::RHI::UnloadShaderProgram(const unsigned int* programKey)
{
	glDeleteProgram(*programKey);
}

void Wrapper::RHI::ActivateTexture(const Resource::Texture& texture, int value)
{
	glActiveTexture(GL_TEXTURE0 + value);
	glBindTexture(GL_TEXTURE_2D, texture.GetTextureKey());
}

void Wrapper::RHI::ActivateCubeMap(const Resource::CubeMap& cubeMap, int value)
{
	glActiveTexture(GL_TEXTURE0 + value);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap.GetKey());
}

void Wrapper::RHI::RenderSubMesh(const unsigned int& VAO, const std::vector<unsigned int> indices)
{
	glBindVertexArray(VAO);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, 0);
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
	// vertex tangents
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Resource::Vertex), (void*)offsetof(Resource::Vertex, tangents));
	// vertex bitangents
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Resource::Vertex), (void*)offsetof(Resource::Vertex, bitangents));

	glBindVertexArray(0);
}

void Wrapper::RHI::SetSubMeshData(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO,
	const std::vector<Resource::SkinnedVertex>& skinnedVertices, const std::vector<unsigned int>& indices)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	int size = sizeof(Resource::SkinnedVertex);
	glBufferData(GL_ARRAY_BUFFER, skinnedVertices.size() * size, &skinnedVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, size, (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, size, (void*)offsetof(Resource::SkinnedVertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, size, (void*)offsetof(Resource::SkinnedVertex, UVCoords));
	// vertex tangents
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, size, (void*)offsetof(Resource::SkinnedVertex, tangents));
	// vertex bitangents
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, size, (void*)offsetof(Resource::SkinnedVertex, bitangents));
	// vertex bone weight index
	glEnableVertexAttribArray(5);
	glVertexAttribIPointer(5, 4, GL_INT, size, (void*)offsetof(Resource::SkinnedVertex, boneIDs));
	// vertex bone weight
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, size, (void*)offsetof(Resource::SkinnedVertex, boneWeights));

	glBindVertexArray(0);
}

void Wrapper::RHI::UnloadSubMesh(const unsigned int& VAO, const unsigned int& VBO, const unsigned int& EBO)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Wrapper::RHI::CreateFrameBuffer(unsigned int* frameBufferKey, unsigned int* renderBufferKey, bool useRenderBuffer)
{
	glGenFramebuffers(1, frameBufferKey);
	glBindFramebuffer(GL_FRAMEBUFFER, *frameBufferKey);
	if (useRenderBuffer)
	{
		// create a renderbuffer object for depth sattachment (we won't be sampling these)
		glGenRenderbuffers(1, renderBufferKey);
		glBindRenderbuffer(GL_RENDERBUFFER, *renderBufferKey);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 69, 69); // use a single renderbufferKey object for both a depth.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *renderBufferKey); // now actually attach it

		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Wrapper::RHI::BindFrameBuffer(unsigned int frameBufferKey, unsigned int renderBufferKey, int width, int height, bool updateSize, bool useRenderBuffer)
{
	if (useRenderBuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferKey);
		glBindRenderbuffer(GL_RENDERBUFFER, renderBufferKey);
	}
	else
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferKey);
	}

	glViewport(0, 0, width, height);
	
}

void Wrapper::RHI::UnbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Wrapper::RHI::ClearFrameBuffer(const Maths::Vec4& clearColor, bool onlyDepth)
{
	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
	glClear(onlyDepth ? GL_DEPTH_BUFFER_BIT: GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Wrapper::RHI::AttachTextureToFrameBuffer(unsigned int textureKey, unsigned int frameBufferKey, bool useDepth)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferKey);

	glFramebufferTexture2D(GL_FRAMEBUFFER, useDepth ? GL_DEPTH_ATTACHMENT : GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D , textureKey, 0);
	if (useDepth)
	{
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Wrapper::RHI::DetachTextureToFrameBuffer(unsigned int frameBufferKey, bool useDepth)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferKey);
	glFramebufferTexture2D(GL_FRAMEBUFFER, useDepth ? GL_DEPTH_ATTACHMENT : GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
}

void Wrapper::RHI::UnloadFrameBuffer(unsigned int* frameBufferKey, unsigned int* renderBufferKey)
{
	glDeleteFramebuffers(1, frameBufferKey);
	glDeleteBuffers(1, renderBufferKey);
}

void Wrapper::RHI::BindCubeMap(unsigned int* cubeMapKey, unsigned char* data[], Resource::Texture* faces[])
{
	glGenTextures(1, cubeMapKey);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *cubeMapKey);

	for (unsigned int i = 0; i < 6; i++)
	{
		if (data[i] && faces[i])
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, faces[i]->GetTextureWidth(), faces[i]->GetTextureHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data[i]
			);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void Wrapper::RHI::UnloadCubeMap(const unsigned int* cubeMapKey)
{
	glDeleteTextures(1, cubeMapKey);
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
std::array<char, 4> Wrapper::RHI::GetPixelColor(Maths::Vec2 viewportSize, Maths::Vec2 TabPos)
{
	glFlush();
	glFinish();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	Engine::Input& input = Engine::Input::GetInstance();
	Maths::Vec2 MPos = input.GetMousePos() + TabPos - Maths::Vec2(20,32);//offset added
	
	Maths::Vec2 WindowS = Wrapper::Window::GetCurrentContext()->GetSize();

	MPos.y = -MPos.y + viewportSize.y;

	std::array<char, 4> data{0};
	glReadPixels(static_cast<int>(MPos.x), static_cast<int>(MPos.y), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data.data());

	return data;
}