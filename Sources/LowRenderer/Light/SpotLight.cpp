// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/ShaderProgram.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Texture.hpp"

#include "Engine/Transform.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"
#include "Engine/MonoBehaviour.hpp"

#include "Wrapper/GUI.hpp"
#include "Wrapper/RHI.hpp"

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
		//shaderProg.SetUniformInt("spotLights[" + std::to_string(number) + "].shadowMap", m_shadowTexture->GetTextureKey());
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

void LowRenderer::SpotLight::RenderShadowMap()
{
	p_shadowFrame->Bind(false);
	p_shadowFrame->Clear();
}

void LowRenderer::SpotLight::Start()
{
	gameobject->GetScene()->GetRenderer()->AddSpotLight(this);
	p_shadowFrame = new FrameBuffer(512, 512, false);
	m_shadowTexture = new Resource::Texture();
	m_shadowTexture->SetData(nullptr, 512, 512, 1);

	m_shadowTexture->BindDepth();
	p_shadowFrame->AttachTexture(m_shadowTexture, true);

}

void LowRenderer::SpotLight::Update()
{
	p_direction = (gameobject->transform->GetGlobalMatrix() * Maths::Vec4(0, -1, 0, 0)).xyz();
	Maths::Vec3 Up = p_direction == Maths::Vec3(0, 1, 0) || p_direction == Maths::Vec3(0, -1, 0) ? Maths::Vec3(0, 0, -1) : Maths::Vec3(0, 1, 0);
	Maths::Vec3 globalPos = Maths::Vec3(gameobject->transform->GetGlobalMatrix().data_4_4[0][3], gameobject->transform->GetGlobalMatrix().data_4_4[1][3], gameobject->transform->GetGlobalMatrix().data_4_4[2][3]);

	Maths::Mat4 proj = Maths::Mat4::CreateProjectionMatrix(90, 1.f, 15000.f, 1);
	Maths::Mat4 view = Maths::Mat4::LookAt(globalPos, globalPos - p_direction, Up);
	float mat[16] = { 0.5, 0, 0, 0.5, 0, 0.5, 0, 0.5, 0, 0, 0.5, 0.5, 0, 0, 0, 1 };
	Maths::Mat4 bias = Maths::Mat4(mat);
	m_VP = view * proj;
}


void LowRenderer::SpotLight::GUIUpdate()
{
	/*if (Wrapper::GUI::CollapsingHeader("Spot Light"))
	{
		Wrapper::GUI::EditColorRGB("Color", p_color);
		Wrapper::GUI::EditFloat("Intensity", p_intensity, true, 0.01f, 0.f, 3.0f);
		Wrapper::GUI::EditFloat("Angle", m_angle, true, 0.1f, 0.f, 360.0f);
		Wrapper::GUI::EditFloat("Linear", m_linearAttenuation, true, 0.001f, 0.f, 1.0f);
		Wrapper::GUI::EditFloat("Quadratic", m_quadraticAttenuation, true, 0.001f, 0.f, 1.0f);
	}*/
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
		result.PosTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("DefaultAssets\\LightIcon.png");
		result.PosModelForTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>("DefaultAssets\\Model\\primitivePlane.obj");
		computed = true;
	}
	return result;
}
