//
// Created by yusuf on 21.05.2026.
//

#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include <filesystem>

#include "miniaudio.h"

class AudioEngine {
    private:
    ma_engine engine;
    ma_sound sound;
    bool soundInitialized = false;

    public:
    AudioEngine();
    ~AudioEngine();


    void play(const std::filesystem::path&);
    void pause();
    void resume();
    void stop();

};

#endif //AUDIOENGINE_H
