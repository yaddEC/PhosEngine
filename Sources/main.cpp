#include <iostream>
#include "Core/Editor.hpp"
#include "Core/ProjectManager.hpp"

int main(int argc, char** argv)
{
	Core::Editor editor;
	Core::ProjectManager PManager;

	PManager.Init();
	PManager.Run();
	PManager.Destroy();

	editor.Init();
	editor.Run();
	editor.Destroy();

	return 0;
}