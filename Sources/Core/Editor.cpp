#include "Core/Editor.hpp"
#include <iostream>

#include "EditorGUI/SceneGUI.hpp"
#include "PhosCore/ShaderProgram.hpp"

using namespace Core;

bool Editor::Init()
{
    if (!InitGLFWWindow()) return false;
    
    if (!InitGlew()) return false;
    

    if (!InitImGui()) return false;
    

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    InitEditorGUI();
    

    return true;
}

void Editor::Run()
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window, &width, &height);

        /* Poll for and process events */
        glfwPollEvents();

        ImGuiNewFrame();
        
        UpdateEditorGUI();

        RenderImGuiFrame();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }
}

void Editor::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete sceneGUI;

    glfwDestroyWindow(window);
    glfwTerminate();
}


bool Core::Editor::InitImGui()
{
    // Set up ImGui
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    return true;
}

bool Core::Editor::InitEditorGUI()
{
    sceneGUI = new EditorGUI::SceneGUI();
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

    window = glfwCreateWindow(1920, 1080, "Phos Editor", nullptr, nullptr);
    if (!window) return false;
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

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
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0, 0.2f, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
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
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::DockSpaceOverViewport(viewport);

    sceneGUI->Update();
}

