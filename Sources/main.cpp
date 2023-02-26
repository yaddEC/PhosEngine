#include <iostream>
#include <PhosCore/Maths.hpp>
#include "HelloWorld.hpp"
int main(int argc, char** argv)
{
	Maths::Vec2 feur(1,2);
	feur *= 2;

	Maths::Vec2 feure(feur);

	std::cout << HelloWorld() << "  " << "x = " << feure.x << " y = " << feure.y << std::endl;
	std::cout << "xy[0] = " << feure.xy[0] << " xy[1] = " << feure.xy[1] << std::endl;
}