#include <iostream>
#include "Core/App.hpp"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>


void Main()
{

	Core::App app;

	app.InitApp();

	/*app.InitProjectManager();
	app.RunProjectManager();
	app.DestroyProjectManager();*/

	app.InitEditor();
	app.RunEditor();
	app.DestroyEditor();

	app.DestroyApp();
}

int main(int argc, char** argv)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(325);
	Main();
	return 0;
}
