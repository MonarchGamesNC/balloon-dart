#include <raylib.h>
#include "timer.h"
#include <iostream>

Timer::Timer() {
    this->lifetimeTime = 0.0f;
    this->callback = [](){};
    this->loop = false;
    this->started = false;
}

Timer::Timer(float time, std::function<void(void)> callback) {
    this->lifetimeTime = time;
    this->callback = callback;
    this->loop = false;
    this->started = false;
}

Timer::Timer(float time, bool looping, std::function<void(void)> callback) {
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
        callback();

        if (loop) {
            lifetimeTime = 3.0f; // TODO: don't hardcode this
        } else {
            started = false;
        }

        return;
    }

    lifetimeTime -= GetFrameTime();
}