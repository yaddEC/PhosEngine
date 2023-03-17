#include "Core/Editor.hpp"
#include <iostream>

#include "EditorGUI/SceneGUI.hpp"
#include "EditorGUI/AssetExplorer.hpp"
#include "Engine/Scene.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Mesh.hpp"
#include "Engine/Input.hpp"
#include "Resource/ShaderProgram.hpp"

#include "RHI/RHI.hpp"
#include "GUI/GUI.hpp"

using namespace Core;

bool Editor::Init()
{
    m_window = RHI::InitWindow(1440, 920, "Phos Engine");
    if (!m_window) return false;
    
    if (!RHI::InitGlew()) return false;
    

    if (!GUI::InitGUI(m_window)) return false;

    RHI::EnableCulling();
    RHI::EnableDepthTest();

    // INIT SCENE TEST
    Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
    rm.Init("Assets");
    Resource::ShaderProgram* sp = rm.GetResource<Resource::ShaderProgram>("Assets\\Shader\\BasicShader.prog");
    Engine::Input::GetInstance().Init(m_window);
    InitEditorGUI();
    m_mainScene = new Engine::Scene();
    m_sceneGUI->SetCurrentScene(m_mainScene);

    

    return true;
}

void Editor::Run()
{
    /* Loop until the user closes the window */
    while (!RHI::WindowShouldClose(m_window))
    {
        m_windowSize = RHI::GetWindowSize(m_window);

        /* Poll for and process events */
        RHI::PollEvents();

        GUI::NewFrame();
        //ImGuiNewFrame();
        
        Engine::Input::GetInstance().Update();
        m_mainScene->Update();
        UpdateEditorGUI();

        GUI::RenderFrame(m_window);
        //RenderImGuiFrame();
        
        /* Swap front and back buffers */
        RHI::SwapBuffer(m_window);
    }
}

void Editor::Destroy()
{
    GUI::DestroyGUI();

    delete m_sceneGUI;
    delete m_mainScene;
    delete m_AssetExplorer;

    RHI::DestroyWindow(m_window);
}


bool Core::Editor::InitImGui()
{
    (void)m_io;
    m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     //  Enable Gamepad Controls
    m_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;          //  Enable Docking
    m_io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;        //  Enable Multi-Viewport / Platform Windows

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init();
    return true;
}

bool Core::Editor::InitEditorGUI()
{
    m_sceneGUI = new EditorGUI::SceneGUI();
    m_AssetExplorer = new EditorGUI::AssetExplorer("Assets");
    return true;
}



void Core::Editor::UpdateEditorGUI()
{
    GUI::DockingSpace();

    m_sceneGUI->Update();
    m_AssetExplorer->Update();
}

