// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------
#include "Resource/Audio.hpp"

#include <iostream>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"


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
    decoder = new ma_decoder;
    deviceConfig = new ma_device_config;
    device = new ma_device;
}
void Resource::Audio::Create()
{

    if (ma_decoder_init_file(GetFilePath().c_str(), NULL, decoder) != MA_SUCCESS) {
        std::cout << "Could not load file\n";
    }

    *deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig->playback.format = decoder->outputFormat;
    deviceConfig->playback.channels = decoder->outputChannels;
    deviceConfig->sampleRate = decoder->outputSampleRate;
    deviceConfig->dataCallback = data_callback;
    deviceConfig->pUserData = decoder;

    if (ma_device_init(NULL, deviceConfig, device) != MA_SUCCESS) {
        std::cout << "Failed to open playback device.\n";
        ma_decoder_uninit(decoder);
        return;
    }
}
Resource::Audio::~Audio()
{
    ma_device_uninit(device);
    ma_decoder_uninit(decoder);

    delete decoder;
    delete deviceConfig;
    delete device;
}

void Resource::Audio::Play(bool isLooping)
{
    ma_decoder_seek_to_pcm_frame(decoder, 0);
    if (isLooping)
        ma_data_source_set_looping(decoder, MA_TRUE);

    if (ma_device_start(device) != MA_SUCCESS) {
        std::cout << "Failed to start playback device.\n";
        ma_device_uninit(device);
        ma_decoder_uninit(decoder);
        return;
    }

}
void Resource::Audio::Stop()
{
    ma_device_stop(device);
    ma_decoder_seek_to_pcm_frame(decoder, 0);
}