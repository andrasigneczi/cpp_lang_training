#include <iostream>
#include <memory>
#include <algorithm>

bool endsWith(const std::string& a, const std::string& b) {
    if (b.size() > a.size()) return false;
        return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
}


// Target interface (adapter)
class MediaPlayerIF {
public:
    virtual void play(std::string fileName) = 0;
};

// Legacy component1 (adaptee)
class Mp4Player {
public:
    void play(std::string fileName) { std::cout << "Mp4Player::play: " << fileName << "\n"; }
};

// Legacy component2 (adaptee)
class VlcPlayer {
public:
    void play(std::string fileName) { std::cout << "VlcPlayer::play: " << fileName << "\n"; }
};



class AdvancedMediaPlayer : public MediaPlayerIF, private Mp4Player, private VlcPlayer {
public:
    void play(std::string fileName) override {
	if(endsWith(fileName, ".mp4")) Mp4Player::play(fileName);
	else if(endsWith(fileName, ".avi")) VlcPlayer::play(fileName);
	else std::cout << "AdvancedMediaPlayer is playing " << fileName << "\n";
    }
};

int main(int argc, char* argv[]) {
    AdvancedMediaPlayer amplayer;
    amplayer.play("01.avi");
    amplayer.play("01.mp4");
    amplayer.play("01.mp3");
    return 0;
}
