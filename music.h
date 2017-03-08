#ifndef MUSIC_H
#define MUSIC_H

#include"Bass/inc/bass.h"
#include<iostream>

class Music
{
public:
    Music();
    ~Music();

    void Play(std::string,bool);
    void Stop();


private:
    int device;
    int freq;
    bool isPlay;
    HSTREAM steamHandle;
};

#endif // MUSIC_H
