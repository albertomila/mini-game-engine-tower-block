#pragma once

class CGameStatus
{
public:
	bool HasSeenTutorial() const { return _hasSeenTutorial; }
	void SetTutorialSeen() { _hasSeenTutorial = true; }

private:
	bool _hasSeenTutorial = false;
};