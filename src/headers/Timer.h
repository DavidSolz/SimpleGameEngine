#ifndef TIMER_H
#define TIMER_H

#include <GLFW/glfw3.h>
#include <stdio.h>

class Timer {

private:

    float timeScale;
    float deltaTime;
    float lastTime;
    int frameCount;

    Timer();

public:

    void TicTac();

    float GetDeltaTime() const;

    float GetTimeScale() const;

    void SetTimeScale(const float& _timeScale);

    static Timer* GetInstance();

    ~Timer();

};

#endif