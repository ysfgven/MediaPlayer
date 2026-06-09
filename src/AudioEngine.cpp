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
    if (soundInitialized) {
        ma_sound_stop(&sound);
        ma_sound_uninit(&sound);
        soundInitialized = false;
    }

    ma_result result = ma_sound_init_from_file(&engine,path.string().c_str(),MA_SOUND_FLAG_STREAM,nullptr, nullptr,&sound);

    if (result == MA_SUCCESS) {
        ma_sound_start(&sound);
        soundInitialized = true;
    }
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

float AudioEngine::getCurrentPosition() {
    float cursor = 0;
    ma_sound_get_cursor_in_seconds(&sound,&cursor);
    return cursor;
}

void AudioEngine::setVolume(float volume) {
    ma_engine_set_volume(&engine,volume / 100.0f);
}

void AudioEngine::seekTo(float seconds) {
    ma_uint64 frame = seconds * ma_engine_get_sample_rate(&engine);
    ma_sound_seek_to_pcm_frame(&sound, frame);

}
