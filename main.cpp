#include <iostream>
#include "MediaLibrary.h"
#include "MediaPlayer.h"

int main() {
    MediaLibrary library;
    library.loadFromDirectory("C:/Users/yusuf/Desktop/test");

    std::cout << "Track count: " << library.getTrackCount() << "\n";

    MediaPlayer player;
    player.setLibrary(&library);

    player.selectTrack(0);
    player.play();
    std::cout << "State: " << player.getStateString() << "\n";

    player.pause();
    std::cout << "State: " << player.getStateString() << "\n";

    player.nextTrack();
    player.play();
    std::cout << "State: " << player.getStateString() << "\n";

    player.stop();
    std::cout << "State: " << player.getStateString() << "\n";
}

