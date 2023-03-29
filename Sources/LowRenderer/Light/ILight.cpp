// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#define LIGHT_EXPORTS
#include "LowRenderer/Light/ILight.hpp"

using namespace LowRenderer;

ILight::ILight() : Engine::MonoBehaviour(true)
{
}
