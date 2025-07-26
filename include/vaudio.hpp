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
#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include <unordered_map> 
#include <string>

class VAudio {
public:
    VAudio();
    ~VAudio();

    bool Init();
    void Shutdown();

    bool LoadMusic(const std::string& id, const std::string& path);
    void PlayMusic(const std::string& id, int loops = -1); // -1 = infinite
    void PauseMusic();
    void ResumeMusic();
    void StopMusic();
    void SetMusicVolume(int volume); // 0–128

    bool LoadSFX(const std::string& id, const std::string& path);
    void PlaySFX(const std::string& id, int loops = 0); // 0 = play once
    void SetSFXVolume(int volume); // 0–128

private:
    std::unordered_map<std::string, Mix_Music*> music_tracks;
    std::unordered_map<std::string, Mix_Chunk*> sound_effects;

    bool initialized = false;

    void FreeAllAudio();
};