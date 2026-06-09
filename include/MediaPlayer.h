//
// Created by yusuf on 21.01.2026.
//

#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "AudioEngine.h"
#include "MediaLibrary.h"

class MediaPlayer {
public:
    enum class State {
        Playing,
        Paused,
        Stopped
    };
    enum class PlayMode {
        Normal,
        Shuffle,
        RepeatOne,
        RepeatAll

    };

private:
    MediaLibrary* library = nullptr;
    size_t currentIndex = 0;
    State currentState = State::Stopped;
    PlayMode currentPlayMode = PlayMode::Normal;
    AudioEngine audioEngine;


public:
    void setLibrary(MediaLibrary* lib);

    float getCurrentPosition();
    void selectTrack(size_t index);
    void nextTrack();
    void previousTrack();

    void play();
    void pause();
    void stop();
    void setVolume(float volume);
    void seekTo(float seconds);
    bool isAtEnd();


    State getState() const;
    const char* getStateString() const;

    const MediaFile* getCurrentTrack() const;
    void setPlayMode(PlayMode mode);
    PlayMode getPlayMode() const;

};

#endif

