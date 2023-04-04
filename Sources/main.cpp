#include <iostream>
#include "Core/App.hpp"

int main(int argc, char** argv)
{
	Core::App app;

	app.InitApp();

	app.InitProjectManager();
	app.RunProjectManager();
	app.DestroyProjectManager();

	app.InitEditor();
	app.RunEditor();
	app.DestroyEditor();

	app.DestroyApp();

	return 0;
}