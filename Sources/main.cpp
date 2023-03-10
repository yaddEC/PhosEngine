#include <iostream>
#include <PhosCore/Maths.hpp>
#include "Core/Application.hpp"

int main(int argc, char** argv)
{
	Application app;
	app.Init();
	app.Run();
	app.Close();

	return 0;
}