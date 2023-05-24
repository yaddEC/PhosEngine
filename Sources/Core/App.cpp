#include "Core/App.hpp"

#include "Wrapper/RHI.hpp"
#include "Wrapper/GUI.hpp"

Core::App::App() :
	m_PManager(nullptr),
	m_editor(nullptr)
{}

Core::App::~App()
{}

bool Core::App::InitApp()
{
	if (!Wrapper::Window::InitGLFW()) return false;
	m_window.Init(Maths::Vec2(1920, 1080), "Phos Editor");
	if (!Wrapper::Window::InitGlew()) return false;
	if (!Wrapper::GUI::InitGUI(m_window.GetWindow())) return false;
	Wrapper::Window::SetSwapInterval(false);
	Wrapper::RHI::EnableCulling();
	Wrapper::RHI::EnableDepthTest();

	//m_PManager = new Core::ProjectManager(m_window);
	m_editor = new Core::Editor(m_window);
	return true;
}

void Core::App::DestroyApp()
{
	Wrapper::GUI::DestroyGUI();
	m_window.Destroy();
	Wrapper::Window::TernimateGLFW();
}


//bool Core::App::InitProjectManager()
//{
//	/eturn m_PManager->Init();
//}
//
//void Core::App::RunProjectManager()
//{
//	m_PManager->Run();
//}
//
//void Core::App::DestroyProjectManager()
//{
//	m_PManager->Destroy();
//	delete(m_PManager);
//}

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