// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/ShaderProgram.hpp"

#include "Engine/Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"
#include "Engine/MonoBehaviour.hpp"

#include "Wrapper/GUI.hpp"

#include "LowRenderer/Renderer.hpp"

#define SPOTLIGHT_EXPORTS
#include "LowRenderer/Light/SpotLight.hpp"


LowRenderer::SpotLight::SpotLight() 
{
	p_color = Maths::Vec3(1);
	m_linearAttenuation = 0.09f;
	m_constantAttenuation = 1.0f;
	m_quadraticAttenuation = 0.032f;
	m_angle = 12.f;
}

LowRenderer::SpotLight::~SpotLight() 
{}

void LowRenderer::SpotLight::Render(const Resource::ShaderProgram& shaderProg, int number)
{
	if (isActive)
	{
		shaderProg.SetUniformVec3("spotLights[" + std::to_string(number) + "].position", transform->position);
		shaderProg.SetUniformVec3("spotLights[" + std::to_string(number) + "].direction", p_direction);

		shaderProg.SetUniformFloat("spotLights[" + std::to_string(number) + "].cutOff", cosf(m_angle * Maths::DEG2RAD));
		shaderProg.SetUniformFloat("spotLights[" + std::to_string(number) + "].outerCutOff", cosf(m_angle * 1.4f * Maths::DEG2RAD));
		
		shaderProg.SetUniformVec3("spotLights[" + std::to_string(number) + "].color", p_color);
		shaderProg.SetUniformFloat("spotLights[" + std::to_string(number) + "].intensity", p_intensity);

		shaderProg.SetUniformFloat("spotLights[" + std::to_string(number) + "].constant", m_constantAttenuation);
		shaderProg.SetUniformFloat("spotLights[" + std::to_string(number) + "].linear", m_linearAttenuation);
		shaderProg.SetUniformFloat("spotLights[" + std::to_string(number) + "].quadratic", m_quadraticAttenuation);
	}
}

void LowRenderer::SpotLight::Start()
{
	gameobject->GetScene()->GetRenderer()->AddSpotLight(this);
}

void LowRenderer::SpotLight::Update()
{
	p_direction = (gameobject->transform->GetGlobalMatrix() * Maths::Vec4(0, -1, 0, 0)).xyz();
}


void LowRenderer::SpotLight::GUIUpdate()
{
	if (Wrapper::GUI::CollapsingHeader("Point Light"))
	{
		Wrapper::GUI::DisplayText("Color: "); Wrapper::GUI::SameLine();
		Wrapper::GUI::EditColorRGB("##Color", p_color);
		Wrapper::GUI::DisplayText("Intensity: "); Wrapper::GUI::SameLine();
		Wrapper::GUI::EditFloat("##Intensity", p_intensity, 0.01f, 0.f, 3.0f);
		Wrapper::GUI::DisplayText("Angle: "); Wrapper::GUI::SameLine();
		Wrapper::GUI::EditFloat("##Angle", m_angle, 0.1f, 0.f, 360.0f);
		Wrapper::GUI::DisplayText("Linear Attenuation: "); Wrapper::GUI::SameLine();
		Wrapper::GUI::EditFloat("##Linear", m_linearAttenuation, 0.001f, 0.f, 1.0f);
		Wrapper::GUI::DisplayText("Quadratic Attenuation: "); Wrapper::GUI::SameLine();
		Wrapper::GUI::EditFloat("##Quadratic", m_quadraticAttenuation, 0.001f, 0.f, 1.0f);
	}
}

void LowRenderer::SpotLight::OnDestroy()
{
	gameobject->GetScene()->GetRenderer()->DeleteSpotLight(this);
}
