#include <iostream>
#include "MediaLibrary.h"
#include "MediaPlayer.h"
#include <thread>
#include <chrono>
int main() {
    MediaLibrary library;
    library.loadFromDirectory("C:/Users/yusuf/Desktop/test");

    std::cout << "Track count: " << library.getTrackCount() << "\n";

    MediaPlayer player;
    player.setLibrary(&library);

    player.selectTrack(0);
    player.play();
    std::this_thread::sleep_for(std::chrono::seconds(10));

    std::cout << "State: " << player.getStateString() << "\n";


}

