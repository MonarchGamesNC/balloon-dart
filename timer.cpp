#include <raylib.h>
#include <iostream>
#include "timer.h"

Timer::Timer() {
    this->lifetimeTime = 0.0f;
    this->callback = [](){};
    this->loop = false;
    this->started = false;
}

Timer::Timer(float time, std::function<void(void)> callback) {
    this->time = time;
    this->lifetimeTime = time;
    this->callback = callback;
    this->loop = false;
    this->started = false;
}

Timer::Timer(float time, bool looping, std::function<void(void)> callback) {
    this->time = time;
    this->lifetimeTime = time;
    this->callback = callback;
    this->loop = looping;
    this->started = false;
}

void Timer::Start() {
    // Start the timer
    if (!started) {
        started = true;
    }
};

void Timer::Tick() {
    // If the timer has not started, do nothing
    if (!started) return;

    // If the timer has expired, call the callback
    if (lifetimeTime <= 0) {
        TraceLog(LOG_DEBUG, "Timer expired");
        // FIXME: using this in balloonSpawner.cpp causes a segfault
        // need to figure out why at a later time but for this project
        // it's not necessary, just keep on chucking through code
        // callback();

        if (loop) {
            lifetimeTime = time;
        } else {
            started = false;
        }

        return;
    }

    lifetimeTime -= GetFrameTime();
    TraceLog(LOG_DEBUG, "Lifetime time: %f", lifetimeTime);
}