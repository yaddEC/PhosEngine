// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------


#include "Wrapper/GUI.hpp"

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
	float max = Maths::Max(m_width, m_height);

	float displayWidth = maxSize * (float)m_width / max;
	float displayHeight = maxSize * (float)m_height / max;

	//GUI::SetCursorPos(Maths::Vec2(GUI::GetCursorPos().x + ((maxSize * 0.5f) - (displayWidth * 0.5f)), 0));
	GUI::SetCursorPos(Maths::Vec2(GUI::GetCursorPos().x + ((maxSize * 0.5f) - (displayWidth * 0.5f)),
		GUI::GetCursorPos().y + ((maxSize * 0.5f) - (displayHeight * 0.5f))));

	GUI::Image(*this, Maths::Vec2(displayWidth, displayHeight));
}

Texture* Texture::GenerateFileIcon()
{
	Texture* tex = new Texture(*this);
	return tex;
}
