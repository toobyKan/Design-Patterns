#include <iostream>
#include <cmath>

class AudioFile {
public:
    virtual int getDuration() const 
    {
        return duration;
    }
protected:
    int duration; 
};

class VideoFile {
public:
    VideoFile(int duration, int frameRate)
    {
        this->duration = duration;
        this->frameRate = frameRate;
    }
    
    int getDuration() const 
    {
        return duration;
    }
    
private:
    int duration;
    int frameRate;
};

class VideoToAudioAdapter : public AudioFile {
private:
    VideoFile *m_videoFile;

public:
    VideoToAudioAdapter(VideoFile *videoFile) : m_videoFile(videoFile) 
    {
        duration = videoFile->getDuration();
    }
};

class AudioPlayer
{
private:
    int maxDuration;
public:
    AudioPlayer(int maxDuration) : maxDuration{maxDuration}
    {}
    
    bool canPlay(AudioFile* audioFile)
    {
        return audioFile->getDuration() <= maxDuration;
    }
};

int main() {
    AudioPlayer audioPlayer(300);
    
    VideoFile* video1 = new VideoFile(200, 30);
    VideoFile* video2 = new VideoFile(400, 30);
    
    VideoToAudioAdapter* adapter1 = new VideoToAudioAdapter(video1);
    VideoToAudioAdapter* adapter2 = new VideoToAudioAdapter(video2);
    
    std::cout << audioPlayer.canPlay(adapter1) << "\n";
    std::cout << audioPlayer.canPlay(adapter2) << "\n";

    delete video1;
    delete video2;
    delete adapter1;
    delete adapter2;

    return 0;
}
