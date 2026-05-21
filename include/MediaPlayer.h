//
// Created by yusuf on 21.01.2026.
//

#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "MediaLibrary.h"

class MediaPlayer {
public:
    enum class State {
        Playing,
        Paused,
        Stopped
    };

private:
    MediaLibrary* library = nullptr;
    size_t currentIndex = 0;
    State currentState = State::Stopped;

public:
    void setLibrary(MediaLibrary* lib);

    void selectTrack(size_t index);
    void nextTrack();
    void previousTrack();

    void play();
    void pause();
    void stop();

    State getState() const;
    const char* getStateString() const;

    const MediaFile* getCurrentTrack() const;

};

#endif

