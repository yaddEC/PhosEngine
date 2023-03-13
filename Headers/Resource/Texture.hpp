#pragma once
#include "IResource.hpp"

namespace Resource
{
	class Texture : public IResource
	{
	public:

		Texture(unsigned char* _data = nullptr, int _width = 1, int _height = 1, int _nrChannels = 3);
		~Texture() { Unload(); }

		void Load(const std::string& filepath) override;
		void SetData(unsigned char* _data, int _width, int _height, int _nrChannel = 3);

		void Bind() override;
		void Unload() override;


		unsigned int GetTextureKey() const { return m_textureKey; }

		unsigned int GetTextureWidth() const { return m_width; }
		unsigned int GetTextureHeight() const { return m_height; }

		//float GetTextureSizeRatio() { return (float)width / (float)height; }

		void ResizeAndReset(int width, int height);

		void DisplayImage(float maxSize);

		Texture* GenerateFileIcon() override;

	private:

		unsigned int m_textureKey;
		int m_width, m_height;
		unsigned char* m_data;
		int m_nrChannels;
	};
}