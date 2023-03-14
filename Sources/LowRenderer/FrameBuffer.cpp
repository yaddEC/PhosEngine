// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Resource/Texture.hpp"
#include <iostream>

#define FRAMEBUFFER_EXPORTS
#include "LowRenderer/Framebuffer.hpp"

using namespace Resource;
using namespace LowRenderer;

FrameBuffer::FrameBuffer(int _width, int _height)
    : m_height(_height), m_width(_width), m_bindedTexture(nullptr)
{
    glGenFramebuffers(1, &m_framebufferKey);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferKey);

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &m_renderbufferKey);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbufferKey);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height); // use a single renderbufferKey object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbufferKey); // now actually attach it

    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Bind(int _width, int _height)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferKey);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbufferKey);

    glViewport(0, 0, _width, _height);

    if (_width == 0 || _height == 0) return;

    // Resize renderbuffer and texture
    if (_width != m_width || _height != m_height)
    {
        if (m_bindedTexture)
        {
            m_bindedTexture->ResizeAndReset(_width, _height);
        }

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
        m_width = _width;
        m_height = _height;
    }
}

void FrameBuffer::Clear(Maths::Vec4 clearColor)
{
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::AttachTexture(Texture* texture)
{
    if (!texture) return;

    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferKey);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->GetTextureKey(), 0);

    texture->ResizeAndReset(m_width, m_height);

    m_bindedTexture = texture;
}

void FrameBuffer::DetachTexture()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferKey);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
    m_bindedTexture = nullptr;
}



void FrameBuffer::Unload()
{
    glDeleteFramebuffers(1, &m_framebufferKey);
    glDeleteBuffers(1, &m_renderbufferKey);
}


