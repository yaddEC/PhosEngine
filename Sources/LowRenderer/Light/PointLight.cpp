// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Wrapper/RHI.hpp"
#include "Resource/ShaderProgram.hpp"

#define POINTLIGHT_EXPORTS
#include "LowRenderer/Light/PointLight.hpp"

LowRenderer::PointLight::PointLight() {}

LowRenderer::PointLight::~PointLight() {}

void LowRenderer::PointLight::Render(const Resource::ShaderProgram& shaderProgrProg, int number)
{

}