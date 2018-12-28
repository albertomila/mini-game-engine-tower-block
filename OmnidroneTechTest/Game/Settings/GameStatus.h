#pragma once

class CGameStatus
{
public:
	void SetPlayTimeId(int playtimeId) { _currentPlayTimeId = playtimeId; }
	int GetPlayTimeId() const { return _currentPlayTimeId; }
	
	bool HasSeenTutorial() const { return _hasSeenTutorial; }
	void SetTutorialSeen() { _hasSeenTutorial = true; }

	void IncreaseMeters(double meters) { _meters += meters; }
	double GetMeters()const { return _meters; }
	void AddPoints(int points) { _points += points; }
	int GetPoints() const { return _points; }

	void SetLives(int lives) { _lives = lives; }
	int GetLives() const { return _lives; }

private:
	bool _hasSeenTutorial = false;
	int _currentPlayTimeId = 0;
	double _meters = 0.0f;
	int _points = 0;
	int _lives = 0;
};