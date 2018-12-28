#pragma once

class CGameStatus
{
public:
	void SetPlayTimeId(int playtimeId) { _currentPlayTimeId = playtimeId; }
	int GetPlayTimeId() const { return _currentPlayTimeId; }
	
	bool HasSeenTutorial() const { return _hasSeenTutorial; }
	void SetTutorialSeen() { _hasSeenTutorial = true; }

	void IncreaseMeters(float meters) { _meters += meters; }
	float GetMeters()const { return _meters; }
	void AddPoints(int points) { _points = points; }
	int GetPoints() const { return _points; }

private:
	bool _hasSeenTutorial = false;
	int _currentPlayTimeId = 0;
	float _meters = 0.0f;
	int _points = 0;
};