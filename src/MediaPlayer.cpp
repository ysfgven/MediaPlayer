//
// Created by yusuf on 21.01.2026.
//

#include "MediaPlayer.h"


void MediaPlayer::play() {
    if (currentMediaFile != nullptr) {
        if (currentState == Stopped) {

            currentState = Playing;

        }
    }

}
void MediaPlayer::pause() {
    if (currentState == Playing) {
        currentState = Paused;
    }

}
void MediaPlayer::stop() {
    if (currentState == Playing) {
    currentState = Stopped;
    }
}
void MediaPlayer::MediaSelect(MediaFile* mediaFile) {
    if (mediaFile != nullptr) {
        currentMediaFile = mediaFile;
        if (currentState == Playing) {
            currentState = Stopped;
        }

    }


}