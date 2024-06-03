#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
#include <vector>
#include <raylib.h>
struct Animation {
    std::string Name;
    std::vector<Vector2> Frames;
    Vector2 CurrentFrame;
    int FramesPerSecond;
    double StartTime;
    bool Finished;
    bool IsLooping;

    void Play();
};

#endif