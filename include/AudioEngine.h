//
// Created by yusuf on 21.05.2026.
//

#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include <filesystem>
#include <thread>
#include <atomic>
#include "miniaudio.h"

class AudioEngine {


    public:
    AudioEngine();
    ~AudioEngine();


    void play(const std::filesystem::path&);
    void pause();
    void resume();
    void stop();

    private:
    ma_engine engine;
    ma_sound sound;
    ma_sound oldSound;
    bool soundInitialized = false;
    bool oldSoundInitialized = false;


};

#endif //AUDIOENGINE_H
