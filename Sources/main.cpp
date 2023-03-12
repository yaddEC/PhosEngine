#include <iostream>
#include <PhosCore/Maths.hpp>
#include "Core/Editor.hpp"

int main(int argc, char** argv)
{
	Core::Editor editor;
	editor.Init();
	editor.Run();
	editor.Destroy();

	return 0;
}