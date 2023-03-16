#include "Core/Editor.hpp"
#include <iostream>

#include "EditorGUI/SceneGUI.hpp"
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
    //InitImGui();

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
    /*ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();*/
    GUI::DestroyGUI();

    delete m_sceneGUI;
    delete m_mainScene;

    /*glfwDestroyWindow(m_window);
    glfwTerminate();*/
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
    return true;
}

bool Core::Editor::InitGLFWWindow()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "FAILED TO INITIALIZE GLFW" << std::endl;
        return false;
    }

    m_window = glfwCreateWindow(1920, 1080, "Phos Editor", nullptr, nullptr);
    if (!m_window) return false;
    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    return true;
}

bool Core::Editor::InitGlew()
{
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return false;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    return true;
}

void Core::Editor::ImGuiNewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Core::Editor::RenderImGuiFrame()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0, 0.2f, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    if (m_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void Core::Editor::UpdateEditorGUI()
{
    // Set docking space
    //ImGuiViewport* viewport = ImGui::GetMainViewport();
    //ImGui::DockSpaceOverViewport(viewport);
    GUI::DockingSpace();

    m_sceneGUI->Update();
}

