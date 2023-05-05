#pragma once
#include "Maths/Maths.hpp"

#include "dllInclude.hpp"


namespace Resource
{
	class Texture;
}

namespace LowRenderer
{
	class PHOSENGINE_API FrameBuffer
	{
	public:
		FrameBuffer(int _width = 0, int _height = 0);
		~FrameBuffer() { Unload(); }

		// Don't resize if at least one parameter is 0 or equal to current width or height
		void Bind(int _width = 0, int _height = 0);

		// Only call AFTER Bind()
		void Clear(Maths::Vec4 clearColor = Maths::Vec4());
		void AttachTexture(Resource::Texture* texture);
		void DetachTexture();

		void Unload();

		inline int GetWidth() { return m_width; }
		inline int GetHeight() { return m_height; }

		inline unsigned int GetFramebufferKey() { return m_framebufferKey; }

		// Return NULL if no texture is binded
		Resource::Texture* GetBindedTexture() { return m_bindedTexture; }

	private:

		int m_width, m_height;
		unsigned int m_framebufferKey, m_renderbufferKey;
		Resource::Texture* m_bindedTexture;

	};
}


