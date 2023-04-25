#include "Core/Editor.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

#include "GUI/EditorGUI/SceneGUI.hpp"
#include "GUI/EditorGUI/AssetExplorer.hpp"
#include "GUI/EditorGUI/HierarchyGUI.hpp"
#include "GUI/EditorGUI/InspectorGUI.hpp"
#include "GUI/EditorGUI/MenuBar.hpp"
#include "GUI/EditorGUI/RendererGUI.hpp"

#include "Engine/Scene.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Mesh.hpp"
#include "Engine/Input.hpp"
#include "Resource/ShaderProgram.hpp"

#include "Wrapper/RHI.hpp"

using namespace Core;
using namespace Wrapper;

Editor::Editor(Wrapper::Window& window )
    : m_window(window)
{}

Editor::~Editor()
{}

bool Editor::Init()
{
    /*typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;
    auto t0 = Time::now();*/
    

    CreateGuiIni();

    // INIT SCENE TEST
    Resource::ResourceManager& rm = Resource::ResourceManager::GetInstance();
    rm.Init("Assets");
    rm.Init("DefaultAssets");
    rm.SetStaticResource();
    

    rm.Reload();

    /*auto t1 = Time::now();
    fsec fs = t1 - t0;
    ms d = std::chrono::duration_cast<ms>(fs);
    std::cout << fs.count() << "s\n";
    std::cout << d.count() << "ms\n";*/

    Engine::Input::GetInstance().Init(m_window.GetWindow());
    InitEditorGUI();
    m_mainScene = rm.GetResource<Engine::Scene>("Assets\\Scene\\SampleScene.phscene");
    m_mainScene->Load(m_mainScene->GetFilePath());
    m_sceneGUI->SetCurrentScene(m_mainScene);
    rm.SetCurrentScene(m_mainScene);
    m_Hierarchy->SetCurrentScene(m_mainScene);
    m_RendererGUI->SetCurrentScene(m_mainScene);
    rm.SetCurrentScene(m_mainScene);
    m_AssetExplorer->Reload();
    

    return true;
}

void Editor::Run()
{
    /* Loop until the user closes the window */
    while (!m_window.ShouldClose())
    {

        /* Poll for and process events */
        m_window.PollEvents();

        GUI::NewFrame();
        
        Engine::Input::GetInstance().Update();
        m_mainScene->Update();
        UpdateEditorGUI();

        GUI::RenderFrame(m_window.GetWindow());
        
        /* Swap front and back buffers */
        m_window.SwapBuffer();
    }
}

void Editor::Destroy()
{

    delete m_sceneGUI;
    delete m_mainScene;
    delete m_AssetExplorer;
    delete m_Hierarchy;
    delete m_MenuBar;
    delete m_RendererGUI;

}

bool Core::Editor::InitEditorGUI()
{
    m_sceneGUI = new EditorGUI::SceneGUI();
    m_Hierarchy = new EditorGUI::HierarchyGUI();
    m_AssetExplorer = new EditorGUI::AssetExplorer("Assets");
    m_Inspector = new EditorGUI::InspectorGUI();
    m_MenuBar = new EditorGUI::MenuBar();
    m_RendererGUI = new EditorGUI::RendererGUI();
    return true;
}

void Core::Editor::CreateGuiIni()
{
    if (std::filesystem::exists("imgui.ini"))
    {
        return;
    }
    std::fstream file("imgui.ini", std::ios_base::out);

    
    file << "[Window][DockSpaceViewport_11111111]\nPos=0,38\nSize=1440,882\nCollapsed=0\n\n";

    file << "[Window][Scene]\nPos=185,38\nSize=985,562\nCollapsed=0\nDockId=0x00000006,0\n\n";

    file << "[Window][Debug##Default]\nPos=60,60\nSize=400,400\nCollapsed=0\n\n";

    file << "[Window][Hierarchy]\nPos=0,38\nSize=183,562\nCollapsed=0\nDockId=0x00000005,0\n\n";

    file << "[Window][Assets]\nPos=0,602\nSize=1170,318\nCollapsed=0\nDockId=0x00000002,0\n\n";

    file << "[Window][Inspector]\nPos=1172,38\nSize=268,882\nCollapsed=0\nDockId=0x00000004,0\n\n";

    file << "[Window][Renderer]\nPos=1172,38\nSize=268,882\nCollapsed=0\nDockId=0x00000004,1\n\n";

    file << "[Docking][Data]\nDockSpace       ID=0x8B93E3BD Window=0xA787BDB4 Pos=60,83 Size=1440,920 Split=X Selected=0xE192E354\n  DockNode      ID=0x00000003 Parent=0x8B93E3BD SizeRef=1170,920 Split=Y\n    DockNode    ID=0x00000001 Parent=0x00000003 SizeRef=1440,600 Split=X Selected=0xE192E354\n      DockNode  ID=0x00000005 Parent=0x00000001 SizeRef=183,600 Selected=0x29EABFBD\n      DockNode  ID=0x00000006 Parent=0x00000001 SizeRef=985,600 CentralNode=1 Selected=0xE192E354\n    DockNode    ID=0x00000002 Parent=0x00000003 SizeRef=1440,318 Selected=0x26CE0345\n  DockNode      ID=0x00000004 Parent=0x8B93E3BD SizeRef=268,920 Selected=0xE7039252\n";

    file.close();
}

void Core::Editor::UpdateEditorGUI()
{
    //---/!\--update_last_what's_supposed_to_be_on_the_screen--/!\---

    GUI::DockingSpace();

    m_sceneGUI->Update();
    m_Hierarchy->Update();
    m_AssetExplorer->Update();

    if (Engine::Scene* newScene = m_AssetExplorer->GetNewScene())
    {
        m_mainScene->Unload();
        m_mainScene = newScene;
        m_mainScene->Load(m_mainScene->GetFilePath());
        m_sceneGUI->SetCurrentScene(m_mainScene);
        m_Hierarchy->SetCurrentScene(m_mainScene);
        m_RendererGUI->SetCurrentScene(m_mainScene);
        Resource::ResourceManager::GetInstance().SetCurrentScene(m_mainScene);
    }
    if (m_Hierarchy->selectedClicked)
    {
        m_Inspector->SetGameObjectToDisplay(m_Hierarchy->GetSelected());
    }
    else if (m_AssetExplorer->GetSelected())
    {
        m_Inspector->SetResourceToDisplay(m_AssetExplorer->GetSelected());
    }
    else if (m_sceneGUI->selectedClicked)
    {
        m_Inspector->SetGameObjectToDisplay(m_sceneGUI->GetSelected());
    }
    
    m_RendererGUI->Update();
    m_Inspector->Update();
    m_MenuBar->Update();
}

