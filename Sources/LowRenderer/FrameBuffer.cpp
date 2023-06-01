// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Resource/Texture.hpp"
#include "Wrapper/RHI.hpp"
#include <iostream>

#include "LowRenderer/Framebuffer.hpp"

using namespace Resource;
using namespace LowRenderer;

FrameBuffer::FrameBuffer(int _width, int _height, bool _useRenderBuffer)
    : m_height(_height), m_width(_width), m_bindedTexture(nullptr)
{
    Wrapper::RHI::CreateFrameBuffer(&m_framebufferKey, &m_renderbufferKey, _useRenderBuffer);
}

void FrameBuffer::Bind(bool useRenderBuffer, int _width, int _height)
{
    Wrapper::RHI::BindFrameBuffer(m_framebufferKey, m_renderbufferKey, m_width, m_height, _width != m_width || _height != m_height, useRenderBuffer);

    if (_width == 0 || _height == 0) return;

    // Resize renderbuffer and texture
    if (_width != m_width || _height != m_height)
    {
        if (m_bindedTexture)
        {
            m_bindedTexture->ResizeAndReset(_width, _height);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
        }
        m_width = _width;
        m_height = _height;
    }
}



void FrameBuffer::Clear(Maths::Vec4 clearColor, bool onlyDepth)
{
    Wrapper::RHI::ClearFrameBuffer(clearColor, onlyDepth);
}

void FrameBuffer::AttachTexture(Texture* texture, bool useDepth)
{
    if (!texture) return;

    Wrapper::RHI::AttachTextureToFrameBuffer(texture->GetTextureKey(), m_framebufferKey, useDepth);

    texture->ResizeAndReset(m_width, m_height);

    m_bindedTexture = texture;
}

void FrameBuffer::DetachTexture()
{
    Wrapper::RHI::DetachTextureToFrameBuffer(m_framebufferKey);
    m_bindedTexture = nullptr;
}



void FrameBuffer::Unload()
{
    Wrapper::RHI::UnloadFrameBuffer(&m_framebufferKey, &m_renderbufferKey);
}


