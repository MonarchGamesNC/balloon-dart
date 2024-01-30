#include <functional>

class Timer {
    public:
        // Take a callback
        Timer();
        Timer(float time, std::function<void(void)> callback);
        Timer(float time, bool looping, std::function<void(void)> callback);
        void Start();
        void Tick();
    private:
        float lifetimeTime;
        bool started = false;
        bool loop = false;
        std::function<void(void)> callback;


};