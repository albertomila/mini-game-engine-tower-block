#pragma once
#include <Engine/Systems/IScreen.h>

class CTextComponent;

class CStackScoreIndicator : public CScreenBase
{
public:
	CStackScoreIndicator();
	~CStackScoreIndicator() override = default;
	void PlayScore(float accuracyNormalized, int points, const sf::Vector2f& worldPosition);
	void Update() override;

private:
	CTextComponent* _scoreText = nullptr;
	CTextComponent* _scoreTextShadow = nullptr;
	double _timeDisplayed = 0;
};

