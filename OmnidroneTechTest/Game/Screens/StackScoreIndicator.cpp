#include "stdafx.h"
#include <Game/Screens/StackScoreIndicator.h>

#include <Engine/UI/ButtonObject.h>
#include <Game/Settings/Settings.h>
#include <Engine/UI/TextObject.h>
#include <Engine/Core/StringUtils.h>

namespace Internal
{
	static const int MAX_FRAMES_DISPLAYING = 1000;
	static const float INCREMENT_POSITION = 0.1f;
}

CStackScoreIndicator::CStackScoreIndicator()
	: CScreenBase("data/Screens/StackScoreIndicator.xml")
{
	const sf::Font& globalFont = CSettings::Get().GetAppConfig().GetGlobalFont();
	_scoreText = GetObjectById<CTextObject>(CStringID("Score"));
	_scoreText->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });

	_scoreTextShadow = GetObjectById<CTextObject>(CStringID("ScoreShadow"));
	_scoreTextShadow->SetFormat(globalFont, 48, sf::Color::Black, { 0, 0 });

	Hide();
}


void CStackScoreIndicator::PlayScore(int points, const sf::Vector2f& position)
{
	std::string pointsText = std::to_string(points);

	sf::Vector2f textfieldPos = position;
	
	_scoreText->GetText().get()->setPosition(textfieldPos);
	_scoreText->SetText(pointsText);

	textfieldPos.x += 5.0f;
	textfieldPos.y += 5.0f;
	_scoreTextShadow->GetText().get()->setPosition(textfieldPos);
	_scoreTextShadow->SetText(pointsText);

	_framesDisplayed = 0;
	Show();
}

void UpdateAnimation(CTextObject& textObject)
{
	sf::Vector2f textfieldPos = textObject.GetText().get()->getPosition();
	textfieldPos.y -= Internal::INCREMENT_POSITION;
	textObject.GetText().get()->setPosition(textfieldPos);
}

void CStackScoreIndicator::Update()
{
	CScreenBase::Update();

	if (IsVisible())
	{
		++_framesDisplayed;

		UpdateAnimation(*_scoreText);
		UpdateAnimation(*_scoreTextShadow);

		if (_framesDisplayed == Internal::MAX_FRAMES_DISPLAYING)
		{
			_framesDisplayed = 0;
			Hide();
		}
	}
}