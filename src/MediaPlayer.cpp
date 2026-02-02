//
// Created by yusuf on 21.01.2026.
//

#include "../include/MediaPlayer.h"

void MediaPlayer::setLibrary(MediaLibrary* lib) {
    stop();
    library = lib;
    currentIndex = 0;
}

void MediaPlayer::selectTrack(size_t index) {
    if (!library) return;
    if (index >= library->getTrackCount()) return;

    stop();
    currentIndex = index;
}

void MediaPlayer::nextTrack() {
    if (!library) return;
    if (currentIndex + 1 >= library->getTrackCount()) return;

    stop();
    currentIndex++;
}

void MediaPlayer::previousTrack() {
    if (!library) return;
    if (currentIndex == 0) return;

    stop();
    currentIndex--;
}

void MediaPlayer::play() {
    if (!library) return;
    if (library->getTrack(currentIndex) == nullptr) return;

    if (currentState == State::Stopped || currentState == State::Paused)
        currentState = State::Playing;
}

void MediaPlayer::pause() {
    if (currentState == State::Playing)
        currentState = State::Paused;
}

void MediaPlayer::stop() {
    if (currentState != State::Stopped)
        currentState = State::Stopped;
}

MediaPlayer::State MediaPlayer::getState() const {
    return currentState;
}

const char* MediaPlayer::getStateString() const {
    switch (currentState) {
        case State::Playing: return "Playing";
        case State::Paused:  return "Paused";
        case State::Stopped: return "Stopped";
        default: return "Unknown";
    }
}


