// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#define LIGHT_EXPORTS
#include "LowRenderer/Light/ILight.hpp"

using namespace LowRenderer;

ILight::ILight()
{
	color = Maths::Vec3(1, 1, 1);
	intensity = 1;
}

ILight::ILight(Maths::Vec3 _color, float _intensity)
{
	color = _color;
	intensity = _intensity;
}
