//
// Created by yusuf on 21.05.2026.
//
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "AudioEngine.h"

AudioEngine::AudioEngine() {
    ma_engine_init(nullptr, &engine);

}

AudioEngine::~AudioEngine() {
    ma_engine_uninit(&engine);
}

void AudioEngine::play(const std::filesystem::path& path) {

    if (soundInitialized == true)
        ma_sound_uninit(&sound);
    ma_sound_init_from_file(&engine,path.string().c_str(),MA_SOUND_FLAG_STREAM,nullptr,nullptr,&sound);
    ma_sound_start(&sound);
    soundInitialized = true;
}

void AudioEngine::pause() {
    ma_sound_stop(&sound);
}

void AudioEngine::resume() {
    ma_sound_start(&sound);
}

void AudioEngine::stop() {
    ma_sound_stop(&sound);
    ma_sound_uninit(&sound);
    soundInitialized = false;
}
