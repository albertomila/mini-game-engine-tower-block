#pragma once
#include <Engine\Systems\ISystem.h>

class CGameTimer : public ISystem
{
public:
	CGameTimer();

	void SetMaxFps(float fps) { _maxFps = fps; }
	float GetFPS() const { return _fps; }
	double GetFrameTime() const { return _currentDt; }
	double GetGameTime() const { return _currentTime; }

	void Init() override {}
	void PreUpdate() override;
	void Update() override {}
	void PostUpdate() override;
	void Shutdown() override {}
    
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