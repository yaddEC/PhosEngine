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
	p_isLooping(false),
	p_audio(nullptr)
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
	
	if (Wrapper::GUI::Button("Play") && p_audio != nullptr)
		p_audio->Play(p_isLooping);
	if (Wrapper::GUI::Button("Stop") && p_audio != nullptr)
		p_audio->Stop();
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
			ClassMemberInfo("isLooping", offsetof(SoundPlayer, SoundPlayer::p_isLooping), MemberType::T_BOOL),
			ClassMemberInfo("Audio", offsetof(SoundPlayer, SoundPlayer::p_audio), MemberType::T_AUDIO)
		};
		//result.PosTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("DefaultAssets\\LightIcon.png");
		//result.PosModelForTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>("DefaultAssets\\Model\\primitivePlane.obj");
		computed = true;
	}
	return result;
}