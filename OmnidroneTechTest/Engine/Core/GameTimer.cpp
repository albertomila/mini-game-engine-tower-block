#include "stdafx.h"
#include <Engine/Core/GameTimer.h>

#include <time.h>
#include <iostream>

namespace Internal
{
	static const float MAX_FPS = 60.f;
	static const float MIN_FPS = 10.f;
}

CGameTimer::CGameTimer()
    : _maxFps(Internal::MAX_FPS)
	, _currentDt(1.f / _maxFps)
    , _maxDt(1.f / _maxFps)
    , _minDt(1.f / Internal::MIN_FPS)
    , _currentTime(0.f)
    , _lastTime(0.f)
    , _currentFrameCount(0)
    , _currentSystemTime(0.f)
    , _lastSystemTime(0.f)
{
}

void CGameTimer::PreUpdate()
{
    _currentSystemTime = GetClockTime();
    double dt = _currentSystemTime - _lastSystemTime;  

    //correction because the breakpoints
    if( dt > _minDt )
    {
        dt = _minDt;
    }

    ++_currentFrameCount;
    _currentDt     = dt;
    _currentTime   += _currentDt;
    _lastTime      = _currentTime;
    _lastSystemTime = _currentSystemTime;
    _fps           = static_cast<float>(1.f / _currentDt);
}

void CGameTimer::PostUpdate()
{
	while ((GetClockTime() - _currentSystemTime) < _maxDt);
}

double CGameTimer::GetClockTime() const
{
    return (double)clock() / 1000.f;
}