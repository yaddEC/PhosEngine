#include "Core/Application.hpp"
#include <iostream>


void Application::Init()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "FAILED TO INITIALIZE GLFW" << std::endl;
        return;
    }

    /* Create a windowed mode window and its OpenGL context */

    window = glfwCreateWindow(1920, 1080, "Phos Engine", NULL, NULL);
    if (!window)
    {
        std::cout << "FAILED TO CREATE A WINDOW" << std::endl;
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));





    // Set up ImGui
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);


}

void Application::Run()
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window, &width, &height);

        /* Poll for and process events */
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.05f, 0.01f, 0.2f, 0.5f));

        // Set docking space
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::DockSpaceOverViewport(viewport);




        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        // ImGui::PopStyleColor();



        // Render ImGui Frame
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGui::EndFrame();


        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);


    }
}

void Application::Close()
{

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    glfwDestroyWindow(window);
    glfwTerminate();
}
