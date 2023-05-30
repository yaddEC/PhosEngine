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
	m_isLooping(false),
	m_audio(nullptr),
	m_volume(1.f)
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
	
	if (Wrapper::GUI::Button("Play") && m_audio != nullptr)
		m_audio->Play(m_isLooping);
	if (Wrapper::GUI::Button("Stop") && m_audio != nullptr)
		m_audio->Stop();
}
void Sound::SoundPlayer::GUIUpdate()
{
	if (m_audio->GetVolume() != m_volume)
		m_audio->SetVolume(m_volume);
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
			ClassMemberInfo("isLooping", offsetof(SoundPlayer, SoundPlayer::m_isLooping), MemberType::T_BOOL),
			ClassMemberInfo("Audio", offsetof(SoundPlayer, SoundPlayer::m_audio), MemberType::T_AUDIO),
			ClassMemberInfo("Volume", offsetof(SoundPlayer, SoundPlayer::m_volume), MemberType::T_FLOAT)
		};
		//result.PosTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("DefaultAssets\\LightIcon.png");
		//result.PosModelForTexture = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>("DefaultAssets\\Model\\primitivePlane.obj");
		computed = true;
	}
	return result;
}

void Sound::SoundPlayer::Play()
{
	m_audio->Play(m_isLooping);
}

void Sound::SoundPlayer::Stop()
{
	m_audio->Stop();
}
