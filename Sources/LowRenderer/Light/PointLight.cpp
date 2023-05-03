// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Wrapper/RHI.hpp"

#include "Resource/ShaderProgram.hpp"

#include "Engine/Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"
#include "Engine/MonoBehaviour.hpp"

#include "Wrapper/GUI.hpp"

#include "LowRenderer/Renderer.hpp"

#include "Resource/ResourceManager.hpp"

#define POINTLIGHT_EXPORTS
#include "LowRenderer/Light/PointLight.hpp"

LowRenderer::PointLight::PointLight() 
{
	p_color = Maths::Vec3(1, 1, 1);
	m_linearAttenuation = 0.09f;
	m_quadraticAttenuation = 0.032f;
}

LowRenderer::PointLight::~PointLight() {}

void LowRenderer::PointLight::Render(const Resource::ShaderProgram& shaderProg, int number)
{
	if (isActive)
	{
		shaderProg.SetUniformVec3("pointLights[" + std::to_string(number) + "].position", transform->position);
		shaderProg.SetUniformVec3("pointLights[" + std::to_string(number) + "].color", p_color);
		shaderProg.SetUniformFloat("pointLights[" + std::to_string(number) + "].intensity", p_intensity);
		shaderProg.SetUniformFloat("pointLights[" + std::to_string(number) + "].constant", 1);
		shaderProg.SetUniformFloat("pointLights[" + std::to_string(number) + "].linear", m_linearAttenuation);
		shaderProg.SetUniformFloat("pointLights[" + std::to_string(number) + "].quadratic", m_quadraticAttenuation);
	}
}

void LowRenderer::PointLight::Start()
{
	gameobject->GetScene()->GetRenderer()->AddPointLight(this);
}

void LowRenderer::PointLight::OnDestroy()
{
	gameobject->GetScene()->GetRenderer()->DeletePointLight(this);
}

void LowRenderer::PointLight::GUIUpdate()
{
	if (Wrapper::GUI::CollapsingHeader("Spot Light"))
	{
		Wrapper::GUI::EditColorRGB("Color", p_color);
		Wrapper::GUI::EditFloat("Intensity", p_intensity, true, 0.001f, 0.f, 3.0f);
		Wrapper::GUI::EditFloat("Linear", m_linearAttenuation, true, 0.001f, 0.f, 1.0f);
		Wrapper::GUI::EditFloat("Quadratic", m_quadraticAttenuation, true, 0.001f, 0.f, 1.0f);
	}
}


Reflection::ClassMetaData& LowRenderer::PointLight::GetMetaData()
{
	using namespace Reflection;

	static bool computed = false;
	static ClassMetaData result;
	if (!computed)
	{
		result.name = "Point Light";
		result.memberList =
		{
			ClassMemberInfo("Color", offsetof(PointLight, PointLight::p_color), MemberType::T_COLOR),
			ClassMemberInfo("Intensity", offsetof(PointLight, PointLight::p_intensity), MemberType::T_FLOAT),
			ClassMemberInfo("Linear Attenuation", offsetof(PointLight, PointLight::m_linearAttenuation), MemberType::T_FLOAT, 0.005f, 0, 1),
			ClassMemberInfo("Quadratic Attenuation", offsetof(PointLight, PointLight::m_quadraticAttenuation), MemberType::T_FLOAT, 0.005f, 0, 1)
		};
		result.PosTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("DefaultAssets\\LightIcon.png");
		result.PosModelForTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>("DefaultAssets\\Model\\primitivePlane.obj");
		computed = true;
	}
	return result;
}
