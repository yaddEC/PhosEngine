// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Sound/SoundPlayer.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/Audio.hpp"
#include "Wrapper/GUI.hpp"

Sound::SoundPlayer::SoundPlayer() : MonoBehaviour(true),
	audio(nullptr),
	selected("None"),
	p_isLooping(false)
{
}

Sound::SoundPlayer::~SoundPlayer()
{
}

void Sound::SoundPlayer::Update()
{
}
void Sound::SoundPlayer::Start()
{
	
}
void Sound::SoundPlayer::OnInspector()
{
	MonoBehaviour::OnInspector();
	if (Wrapper::GUI::Combo("Skybox : ", Resource::ResourceManager::GetInstance().GetResourceNameList<Resource::Audio>(), selected, "None"))
	{
		if (selected != "None")
		{
			audio = Resource::ResourceManager::GetInstance().GetResource<Resource::Audio>(selected);
		}
	}
	if (Wrapper::GUI::Button("Play") && audio != nullptr)
		audio->Play(p_isLooping);
	if (Wrapper::GUI::Button("Stop") && audio != nullptr)
		audio->Stop();
}
void Sound::SoundPlayer::GUIUpdate()
{

}
void Sound::SoundPlayer::OnDestroy()
{

}
Reflection::ClassMetaData& Sound::SoundPlayer::GetMetaData()
{
	using namespace Reflection;

	static bool computed = false;
	static ClassMetaData result;
	if (!computed)
	{
		result.name = "Sound";
		result.memberList =
		{
			ClassMemberInfo("isLooping", offsetof(SoundPlayer, p_isLooping), MemberType::T_BOOL),
		};
		//result.PosTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("DefaultAssets\\LightIcon.png");
		//result.PosModelForTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>("DefaultAssets\\Model\\primitivePlane.obj");
		computed = true;
	}
	return result;
}