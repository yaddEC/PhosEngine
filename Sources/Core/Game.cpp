#include "Core/Game.hpp"
#include "Wrapper/Window.hpp"
#include "LowRenderer/Framebuffer.hpp"
#include "Resource/ResourceManager.hpp"
#include "Wrapper/RHI.hpp" 
#include "LowRenderer/CameraComponent.hpp"
#include "Resource/ShaderProgram.hpp"

void Game::Update(Engine::Scene* scene)
{
	scene->GetRenderer()->RenderAll(nullptr, Wrapper::Window::GetCurrentContext()->GetSize(), true);
	int cameraCount = scene->GetRenderer()->GetCameraList().size();

    if (cameraCount)
    {
        Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
        Wrapper::RHI::UnbindFrameBuffer();
        Wrapper::RHI::ClearFrameBuffer(Maths::Vec4(0, 0, 0, 1));
        rm.gameShader->Use();
        rm.gameShader->SetTexture("screenTexture[0]", 0, scene->GetRenderer()->GetCameraList()[0]->GetRenderTexture());
        Wrapper::RHI::RenderSubMesh(rm.quad->GetSubMesh(0).GetVAO(), rm.quad->GetSubMesh(0).indices);
    }
    
}
