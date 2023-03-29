#include "Core/Editor.hpp"
#include <iostream>
#include <fstream>

#include "EditorGUI/SceneGUI.hpp"
#include "EditorGUI/AssetExplorer.hpp"
#include "EditorGUI/HierarchyGUI.hpp"
#include "EditorGUI/InspectorGUI.hpp"
#include "Engine/Scene.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Mesh.hpp"
#include "Engine/Input.hpp"
#include "Resource/ShaderProgram.hpp"

#include "Wrapper/RHI.hpp"
#include "Wrapper/GUI.hpp"

using namespace Core;
using namespace Wrapper;

bool Editor::Init()
{
    CreateGuiIni();

    m_window = Wrapper::RHI::InitWindow(1440, 920, "Phos Engine");
    if (!m_window) return false;
    
    if (!Wrapper::RHI::InitGlew()) return false;
    

    if (!GUI::InitGUI(m_window)) return false;

    Wrapper::RHI::EnableCulling();
    Wrapper::RHI::EnableDepthTest();

    // INIT SCENE TEST
    Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
    rm.Init("Assets");
    rm.Init("DefaultAssets");
    rm.Reload();
    Engine::Input::GetInstance().Init(m_window);
    InitEditorGUI();
    m_mainScene = new Engine::Scene();
    m_sceneGUI->SetCurrentScene(m_mainScene);
    m_Hierarchy->SetCurrentScene(m_mainScene);
    m_AssetExplorer->Reload();
    

    return true;
}

void Editor::Run()
{
    /* Loop until the user closes the window */
    while (!Wrapper::RHI::WindowShouldClose(m_window))
    {
        m_windowSize = Wrapper::RHI::GetWindowSize(m_window);

        /* Poll for and process events */
        Wrapper::RHI::PollEvents();

        GUI::NewFrame();
        
        Engine::Input::GetInstance().Update();
        m_mainScene->Update();
        UpdateEditorGUI();

        GUI::RenderFrame(m_window);
        
        /* Swap front and back buffers */
        Wrapper::RHI::SwapBuffer(m_window);
    }
}

void Editor::Destroy()
{
    GUI::DestroyGUI();

    delete m_sceneGUI;
    delete m_mainScene;
    delete m_AssetExplorer;
    delete m_Hierarchy;

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
    m_Hierarchy = new EditorGUI::HierarchyGUI();
    m_AssetExplorer = new EditorGUI::AssetExplorer("Assets");
    m_Inspector = new EditorGUI::InspectorGUI();
    return true;
}

void Core::Editor::CreateGuiIni()
{
    if (std::filesystem::exists("imgui.ini"))
    {
        return;
    }
    std::fstream file("imgui.ini", std::ios_base::out);

    
    file << "[Window][DockSpaceViewport_11111111]\nPos=0,0\nSize=1440,920\nCollapsed=0\n\n";

    file << "[Window][Scene]\nPos=185,0\nSize=985,600\nCollapsed=0\nDockId=0x00000006,0\n\n";

    file << "[Window][Debug##Default]\nPos=60,60\nSize=400,400\nCollapsed=0\n\n";

    file << "[Window][Hierarchy]\nPos=0,0\nSize=183,600\nCollapsed=0\nDockId=0x00000005,0\n\n";

    file << "[Window][Assets]\nPos=0,602\nSize=1170,318\nCollapsed=0\nDockId=0x00000002,0\n\n";

    file << "[Window][Inspector]\nPos=1172,0\nSize=268,920\nCollapsed=0\nDockId=0x00000004,0\n\n";

    file << "[Docking][Data]\nDockSpace       ID=0x8B93E3BD Window=0xA787BDB4 Pos=60,83 Size=1440,920 Split=X Selected=0xE192E354\n  DockNode      ID=0x00000003 Parent=0x8B93E3BD SizeRef=1170,920 Split=Y\n    DockNode    ID=0x00000001 Parent=0x00000003 SizeRef=1440,600 Split=X Selected=0xE192E354\n      DockNode  ID=0x00000005 Parent=0x00000001 SizeRef=183,600 Selected=0x29EABFBD\n      DockNode  ID=0x00000006 Parent=0x00000001 SizeRef=985,600 CentralNode=1 Selected=0xE192E354\n    DockNode    ID=0x00000002 Parent=0x00000003 SizeRef=1440,318 Selected=0x26CE0345\n  DockNode      ID=0x00000004 Parent=0x8B93E3BD SizeRef=268,920 Selected=0xE7039252\n";

    file.close();
}

void Core::Editor::UpdateEditorGUI()
{
    GUI::DockingSpace();

    m_sceneGUI->Update();
    m_Hierarchy->Update();
    m_AssetExplorer->Update();
    m_Inspector->SetGameObjectToDisplay(m_Hierarchy->GetSelected());
    m_Inspector->Update();
}

