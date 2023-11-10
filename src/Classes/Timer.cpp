#include "Timer.h"

static Timer* instance;

Timer::Timer(){
    this->timeScale = 1.0f;
    this->lastTime = glfwGetTime();
}

void Timer::TicTac(){
    float currentTime = glfwGetTime();
    frameCount++;
    float delta = currentTime - lastTime;
    if(delta >= 1.0f){
            
        deltaTime = delta/timeScale;
        frameCount = 0;
        lastTime = currentTime;
    }
}

float Timer::GetTimeScale() const{
    return timeScale;
}

float Timer::GetDeltaTime() const{
    return deltaTime;
}

void Timer::SetTimeScale(const float& _timeScale){
        this->timeScale = _timeScale;
}

Timer* Timer::GetInstance(){
    if(!instance)
        instance = new Timer();

    return instance;
}

Timer::~Timer(){
    delete instance;
}