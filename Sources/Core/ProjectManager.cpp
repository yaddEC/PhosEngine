#include "Core/ProjectManager.hpp"
#include "GUI/ProjectManagerGUI/ProjectManagerGUI.hpp"

#include "Wrapper/RHI.hpp"

Core::ProjectManager::ProjectManager(GLFWwindow* window) :
	m_window(window)
{

}

Core::ProjectManager::~ProjectManager()
{

}

bool Core::ProjectManager::Init()
{
	InitProjectManagerGUI();
	return true;
}

void Core::ProjectManager::Run()
{
	while (!Wrapper::RHI::WindowShouldClose(m_window))
	{
		Wrapper::RHI::PollEvents();
		Wrapper::GUI::NewFrame();

		UpdateProjectManagerGUI();

		Wrapper::GUI::RenderFrame(m_window);
		Wrapper::RHI::SwapBuffer(m_window);
	}
}

void Core::ProjectManager::Destroy()
{
	delete m_PManagerGUI;
}

bool Core::ProjectManager::InitProjectManagerGUI()
{
	m_PManagerGUI = new ProjectManagerGUI::ProjectManagerGUI();
	return true;
}

void Core::ProjectManager::UpdateProjectManagerGUI()
{
	Wrapper::GUI::DockingSpace();
	m_PManagerGUI->Update();
}