#pragma once
#include <Engine\Core\Singleton.h>

class CGameTimer : public CSingleton<CGameTimer>
{
public:
    CGameTimer();
    
	void SetMaxFps(float fps) { _maxFps = fps; }
	float GetFPS() const { return _fps; }
	double GetFrameTime() const { return _currentDt; }
	double GetGameTime() const { return _currentTime; }

    void PreUpdate();
    void PostUpdate();
    
private:
    double GetClockTime() const;

private:
	float _maxFps;
    float  _fps;
    long long  _currentFrameCount;
    double _minDt;
    double _maxDt;

    double _currentSystemTime;
    double _lastSystemTime;

    double _currentDt;
    double _currentTime;
    double _lastTime;
};