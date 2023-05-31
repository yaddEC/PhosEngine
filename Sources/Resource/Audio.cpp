// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include "Resource/Audio.hpp"

#include <iostream>
#include <algorithm>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"

static bool initEngine = false;
static ma_engine engine;
static ma_engine_config engineConfig;

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }

    ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

    (void)pInput;
}

Resource::Audio::Audio()
{
    if (!initEngine)
    {
        initEngine = true;
        engineConfig = ma_engine_config_init();

        if (ma_engine_init(&engineConfig, &engine) != MA_SUCCESS) {
            assert("cant init audio");
        }
    }
    sound = new ma_sound;
}

void Resource::Audio::Create()
{
    if (ma_sound_init_from_file(&engine, GetFilePath().c_str(), 0, NULL, NULL, sound) != MA_SUCCESS) {
        std::cout << "Could not load file\n";
    }
}

Resource::Audio::~Audio()
{
    //ma_sound_uninit(sound);

    delete sound;
}

void Resource::Audio::Play(bool isLooping)
{
    //if (isLooping)
       // ma_data_source_set_looping(decoder, MA_TRUE);
    ma_sound_set_looping(sound, isLooping);

    ma_sound_start(sound);
}
void Resource::Audio::Stop()
{
    ma_sound_stop(sound);
}

void Resource::Audio::SetVolume(float value)
{
    ma_sound_set_volume(sound, std::max(0.f, value));
}

float Resource::Audio::GetVolume()
{
    return ma_sound_get_volume(sound);
}