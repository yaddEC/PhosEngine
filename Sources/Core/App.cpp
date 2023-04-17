#include "Core/App.hpp"

#include "Wrapper/RHI.hpp"
#include "Wrapper/GUI.hpp"

Core::App::App() :
	m_PManager(nullptr),
	m_editor(nullptr),
	m_window(nullptr)
{}

Core::App::~App()
{}

bool Core::App::InitApp()
{
	m_window = Wrapper::RHI::InitWindow(1440, 920, "Phos Engine");
	if (!m_window) return false;
	if (!Wrapper::RHI::InitGlew()) return false;
	if (!Wrapper::GUI::InitGUI(m_window)) return false;

	Wrapper::RHI::EnableCulling();
	Wrapper::RHI::EnableDepthTest();
	//Wrapper::RHI::SwapInterval(false);

	m_PManager = new Core::ProjectManager(m_window);
	m_editor = new Core::Editor(m_window, m_windowSize);
}

void Core::App::DestroyApp()
{
	Wrapper::GUI::DestroyGUI();
	Wrapper::RHI::DestroyWindow(m_window);

}


bool Core::App::InitProjectManager()
{
	return m_PManager->Init();
}
void Core::App::RunProjectManager()
{
	m_PManager->Run();
}
void Core::App::DestroyProjectManager()
{
	m_PManager->Destroy();
	delete(m_PManager);
}

bool Core::App::InitEditor()
{
	return m_editor->Init();
}
void Core::App::RunEditor()
{
	m_editor->Run();
}
void Core::App::DestroyEditor()
{
	m_editor->Destroy();
	delete(m_editor);
}