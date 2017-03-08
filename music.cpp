#include "music.h"

Music::Music()
{
    device=-1;
    freq=44100;
    BASS_Init(device,freq,0,0,NULL);
    isPlay=false;
}

Music::~Music()
{
    BASS_Free();
}

void Music::Play(std::string path,bool loop)
{
    if(loop)
    {
        steamHandle=BASS_StreamCreateFile(FALSE,path.c_str(),0,0,BASS_SAMPLE_LOOP);
    }
    else
    {
        steamHandle=BASS_StreamCreateFile(FALSE,path.c_str(),0,0,0);
    }

    BASS_ChannelPlay(steamHandle,TRUE);
}

void Music::Stop()
{
    BASS_ChannelStop(steamHandle);
}
