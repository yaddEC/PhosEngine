#include "GUI/EditorGUI/CanvasEditor.hpp"
#include "Wrapper/GUI.hpp"


EditorGUI::CanvasEditor::CanvasEditor()
	: IGUI("Canvas Editor", true)
	, m_framebuffer(LowRenderer::FrameBuffer(10, 10))
	, m_renderTexture(Resource::Texture())
{
	m_renderTexture.Bind();
	m_framebuffer.AttachTexture(&m_renderTexture);
}

void EditorGUI::CanvasEditor::DoUpdate()
{
	if (m_currentCanvas)
	{
		m_framebuffer.Bind(true, p_size.x, p_size.y - 42);
		m_framebuffer.Clear();
		m_currentCanvas->RenderUI(p_size - Maths::Vec2(0, 42));
		Wrapper::GUI::Image(m_renderTexture, p_size - Maths::Vec2(0, 42));
	}

}
