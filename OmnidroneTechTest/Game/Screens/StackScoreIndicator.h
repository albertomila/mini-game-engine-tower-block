#pragma once
#include <Engine/Systems/IScreen.h>

class CTextComponent;

class CStackScoreIndicator : public CScreenBase
{
public:
	CStackScoreIndicator();
	~CStackScoreIndicator() override = default;
	void PlayScore(int points, const sf::Vector2f& position);
	void Update() override;

private:
	CTextComponent* _scoreText = nullptr;
	CTextComponent* _scoreTextShadow = nullptr;
	double _timeDisplayed = 0;
};

