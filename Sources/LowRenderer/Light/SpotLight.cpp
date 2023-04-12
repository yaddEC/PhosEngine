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
	if (Wrapper::GUI::CollapsingHeader("Spot Light"))
	{
		Wrapper::GUI::EditColorRGB("Color", p_color);
		Wrapper::GUI::EditFloat("Intensity", p_intensity, true, 0.01f, 0.f, 3.0f);
		Wrapper::GUI::EditFloat("Angle", m_angle, true, 0.1f, 0.f, 360.0f);
		Wrapper::GUI::EditFloat("Linear", m_linearAttenuation, true, 0.001f, 0.f, 1.0f);
		Wrapper::GUI::EditFloat("Quadratic", m_quadraticAttenuation, true, 0.001f, 0.f, 1.0f);
	}
}

void LowRenderer::SpotLight::OnDestroy()
{
	gameobject->GetScene()->GetRenderer()->DeleteSpotLight(this);
}

Reflection::ClassMetaData& LowRenderer::SpotLight::GetMetaData()
{
	using namespace Reflection;

	static bool computed = false;
	static ClassMetaData result;
	if (!computed)
	{
		result.name = "Spot Light";
		result.memberList =
		{
			ClassMemberInfo("Color", offsetof(SpotLight, SpotLight::p_color), MemberType::T_COLOR),
			ClassMemberInfo("Intensity", offsetof(SpotLight, SpotLight::p_intensity), MemberType::T_FLOAT, 0.1f, 0, 10),
			ClassMemberInfo("Angle", offsetof(SpotLight, SpotLight::m_angle), MemberType::T_FLOAT, 0.01f, 0, 90),
			ClassMemberInfo("Linear Attenuation", offsetof(SpotLight, SpotLight::m_linearAttenuation), MemberType::T_FLOAT, 0.005f, 0, 1),
			ClassMemberInfo("Quadratic Attenuation", offsetof(SpotLight, SpotLight::m_quadraticAttenuation), MemberType::T_FLOAT, 0.005f, 0, 1)
		};
		computed = true;
	}
	return result;
}
