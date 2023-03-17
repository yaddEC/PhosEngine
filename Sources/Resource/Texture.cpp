// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <GL/glew.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>

#include "Wrapper/RHI.hpp"

#define TEXTURE_EXPORTS
#include "Resource/Texture.hpp"

using namespace Resource;

Texture::Texture(unsigned char* _data, int _width, int _height, int _nrChannels)
	: IResource()
	, m_data(_data)
	, m_width(_width)
	, m_height(_height)
	, m_nrChannels(_nrChannels)
{

}

void Texture::Load(const std::string& filepath)
{
	SetFileInfo(filepath);

	stbi_set_flip_vertically_on_load(true);
	m_data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_nrChannels, STBI_rgb_alpha);
	/*if (nrChannels == 3) nrChannels = 4;
	if (nrChannels == 4) nrChannels = 3;*/
}

void Texture::SetData(unsigned char* _data, int _width, int _height, int _nrChannel)
{
	m_data = _data;
	m_width = _width;
	m_height = _height;
	m_nrChannels = _nrChannel;
}

void Texture::Bind()
{
	Wrapper::RHI::BindTexture(&m_textureKey, m_data, m_nrChannels, m_width, m_height);
	if (m_data)
	{
		stbi_image_free(m_data);
	}
	p_isLoaded = true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &m_textureKey);
}

void Texture::ResizeAndReset(int _width, int _height)
{
	if (m_width <= 0 || m_height <= 0) return;

	m_width = _width;
	m_height = _height;

	Wrapper::RHI::ResizeTexture(&m_textureKey, m_nrChannels, m_width, m_height);
}

void Texture::DisplayImage(float maxSize)
{
	//float max = LMath::Max(width, height);

	//float displayWidth = maxSize * (float)width / max;
	//float displayHeight = maxSize * (float)height / max;

	//ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ((maxSize * 0.5f) - (displayWidth * 0.5f)));
	//ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ((maxSize * 0.5f) - (displayHeight * 0.5f)));

	//ImGui::Image(
	//	(ImTextureID)textureKey,
	//	ImVec2(displayWidth, displayHeight),
	//	ImVec2(0, 1),
	//	ImVec2(1, 0)
	//);
}

Texture* Texture::GenerateFileIcon()
{
	Texture* tex = new Texture(*this);
	return tex;
}
