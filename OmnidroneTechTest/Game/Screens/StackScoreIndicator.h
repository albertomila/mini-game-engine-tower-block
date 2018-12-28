#pragma once
#include <Engine/Systems/IScreen.h>

class CTextObject;

class CStackScoreIndicator : public CScreenBase
{
public:
	CStackScoreIndicator();
	~CStackScoreIndicator() override = default;
	void PlayScore(int points, const sf::Vector2f& position);
	void Update() override;

private:
	CTextObject* _scoreText = nullptr;
	CTextObject* _scoreTextShadow = nullptr;
	int _framesDisplayed = 0;
};

