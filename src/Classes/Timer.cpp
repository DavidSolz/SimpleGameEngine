#include "Timer.h"

static Timer* instance;

Timer::Timer(){
    this->timeScale = 1.0f;
    this->lastTime = glfwGetTime();
    this->deltaTime = 1.0f/60;
}

void Timer::TicTac(){
    float currentTime = glfwGetTime();
    frameCount++;
    float delta = currentTime - lastTime;
    if(delta >= 1.0f){
        deltaTime = 1000.0f/frameCount;
        frameCount = 0;
        lastTime = currentTime;

        fprintf(stdout, "Frametime: %0.4fms\r", deltaTime);
        fflush(stdout);
    }
}

float Timer::GetTimeScale() const{
    return timeScale;
}

float Timer::GetDeltaTime() const{
    return deltaTime * timeScale;
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
