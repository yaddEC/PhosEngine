#pragma once
#include "GUI/IGUI.hpp"
#include "UI/Canvas.hpp"
#include "LowRenderer/Framebuffer.hpp"
#include "Resource/Texture.hpp"
 

namespace EditorGUI
{
	class CanvasEditor : public APPGUI::IGUI
	{
	public:
		CanvasEditor();


		void DoUpdate() override;

		void SetCanvas(UI::Canvas* newCanvas) { m_currentCanvas = newCanvas; }

	private:

		LowRenderer::FrameBuffer m_framebuffer;
		Resource::Texture m_renderTexture;
		UI::Canvas* m_currentCanvas = nullptr;
		 
	};
}
