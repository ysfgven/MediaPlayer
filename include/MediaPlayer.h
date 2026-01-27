//
// Created by yusuf on 21.01.2026.
//

#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H
#include "MediaLibrary.h"


class MediaPlayer {
private:

    enum State {
        Playing,
        Paused,
        Stopped,
    };
    State currentState = State::Stopped;
    MediaFile* currentMediaFile;

    public:
    void play();
    void pause();
    void stop();
    void MediaPlayer::MediaSelect(MediaFile* mediaFile);

};



#endif //MEDIAPLAYER_H
