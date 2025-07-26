/**
 * include/vaudio.hpp
 * 2025 (c) wellbutteredsoftware
 * Licensed under Apache-2.0
 * 
 * Audio backend, handled by SDL3_mixer under the branch `sdl2-api-on-sdl3`.
 * Right now only .WAV audio files are supported and are recommended to use.
 * Future support for .OGG files is in the works!
 * 
 * Support for other formats like FLAC and MPEG-3 may be considered.
 */

#include <SDL3/SDL_audio.h>
#include <vector>
#include <mutex>    
#include <string>

class VAudio {
public:
    VAudio();
    ~VAudio();

    bool Init(int sampleRate = 48000, SDL_AudioFormat format = SDL_AUDIO_F32, int channels = 2, int bufferSize = 4096);
    void Shutdown();

    // Playback methods (raw audio data)
    bool LoadWAV(const std::string& path); // one-shot test method for now
    void PlayAudio(const Uint8* data, Uint32 length);

    void Pause();
    void Resume();
    void Stop();

private:
    SDL_AudioDeviceID audioDevice = 0;
    SDL_AudioSpec audioSpec{};

    std::vector<Uint8> queuedData;
    std::mutex queueMutex;
    bool initialized = false;
};