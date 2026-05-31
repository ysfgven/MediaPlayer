//
// Created by yusuf on 21.01.2026.
//

#include "../include/MediaPlayer.h"
#include <random>

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

    if (currentPlayMode == PlayMode::RepeatOne) {
        stop();
        play();
        return;
    }

    stop();

    if (currentPlayMode == PlayMode::Normal) {
        if (currentIndex + 1 >= library->getTrackCount())
            return;
        currentIndex++;

    } else if (currentPlayMode == PlayMode::RepeatAll) {
        currentIndex + 1 >= library->getTrackCount() ? currentIndex = 0 : currentIndex++;

    } else if (currentPlayMode == PlayMode::Shuffle) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> randBoundries(0, int(library->getTrackCount() - 1));
        currentIndex = randBoundries(gen);
    }

    play();
}

void MediaPlayer::previousTrack() {
    if (!library) return;
    if (currentPlayMode == PlayMode::RepeatOne) {
        return;
    }
    if (currentIndex == 0) {
        stop();
        return;
    }

    stop();
    currentIndex--;
    play();
}

void MediaPlayer::play() {
    if (!library) return;
    if (library->getTrack(currentIndex) == nullptr) return;

    audioEngine.play(getCurrentTrack()->getFilePath());
    currentState = State::Playing;
}

void MediaPlayer::pause() {
    if (currentState == State::Playing) {
        audioEngine.pause();
        currentState = State::Paused;
    }

}

void MediaPlayer::stop() {
    if (currentState != State::Stopped) {
        audioEngine.stop();
        currentState = State::Stopped;
    }
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

const MediaFile* MediaPlayer::getCurrentTrack() const {
        if (library == nullptr)
            return nullptr;
        return library->getTrack(currentIndex);
}

void MediaPlayer::setPlayMode(PlayMode mode) {
    currentPlayMode = mode;
}

MediaPlayer::PlayMode MediaPlayer::getPlayMode() const {
    return currentPlayMode;
}


