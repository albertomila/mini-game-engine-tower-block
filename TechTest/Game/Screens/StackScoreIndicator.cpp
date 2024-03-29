#include "stdafx.h"
#include <Game/Screens/StackScoreIndicator.h>

#include <Engine/UI/ButtonComponent.h>
#include <Game/Settings/Settings.h>
#include <Engine/UI/TextComponent.h>
#include <Engine/Core/StringUtils.h>
#include <Engine/Core/GameTimer.h>
#include <Engine/Systems/MainWindow.h>
#include <Engine/Systems/SystemManager.h>
#include <Engine/Core/MathUtils.h>

namespace Internal
{
	static const float MAX_SECONDS_DISPLAYED = 0.6f;
	static const float INCREMENT_POSITION = 1.6f;
}

CStackScoreIndicator::CStackScoreIndicator()
	: CScreenBase("data/Screens/StackScoreIndicator.xml")
{
	const sf::Font& globalFont = CSettings::Get().GetAppConfig().GetGlobalFont();
	_scoreText = GetComponentObjectById<CTextComponent>(CStringID("Score"));
	_scoreText->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });

	_scoreTextShadow = GetComponentObjectById<CTextComponent>(CStringID("ScoreShadow"));
	_scoreTextShadow->SetFormat(globalFont, 48, sf::Color::Black, { 0, 0 });

	Hide();
}

void CStackScoreIndicator::PlayScore(float accuracyNormalized, int points, const sf::Vector2f& worldPosition)
{
	CMainWindow* mainWindow = CSystemManager::Get().GetSystem<CMainWindow>();
	sf::Vector2i uiPosition = mainWindow->GerRenderWindow().mapCoordsToPixel(worldPosition);


	const STowerBlockScoreDescriptor& towerBlockScoreDescriptor = CSettings::Get().GetGameConfig().GetTowerBlockScoreDescriptor();
	std::string accuracyFeedback;
	if (accuracyNormalized > towerBlockScoreDescriptor._perfectStackAccuracy)
	{
		accuracyFeedback = towerBlockScoreDescriptor._messagePerfect;
	}
	else if (accuracyNormalized > towerBlockScoreDescriptor._goodStackAccuracy)
	{
		accuracyFeedback = towerBlockScoreDescriptor._messageGood;
	}
	else if (accuracyNormalized < 0.0f || MathUtils::IsFloatEqual(accuracyNormalized, 0.0f))
	{
		accuracyFeedback = towerBlockScoreDescriptor._messageFail;
	}

	std::string pointsText;
	if (points > 0)
	{
		pointsText += std::to_string(points) + " ";
	}
	
	pointsText += accuracyFeedback;

	sf::Vector2f textfieldPos;
	textfieldPos.x = static_cast<float>(uiPosition.x);
	textfieldPos.y = static_cast<float>(uiPosition.y);
	
	_scoreText->GetObject().SetPosition(textfieldPos);
	_scoreText->SetText(pointsText);


	sf::Vector2f shadowTextfieldPos = textfieldPos;
	shadowTextfieldPos.x += 5.0f;
	shadowTextfieldPos.y += 5.0f;
	_scoreTextShadow->GetObject().SetPosition(shadowTextfieldPos);
	_scoreTextShadow->SetText(pointsText);

	_timeDisplayed = 0.0;
	Show();
}

void UpdateAnimation(CTextComponent& textComponent)
{
	sf::Vector2f textfieldPos = textComponent.GetObject().GetTransform().getPosition();
	textfieldPos.y -= Internal::INCREMENT_POSITION;
	textComponent.GetObject().SetPosition(textfieldPos);
}

void CStackScoreIndicator::Update()
{
	CScreenBase::Update();

	if (IsVisible())
	{
		_timeDisplayed += CSystemManager::Get().GetSystem<CGameTimer>()->GetFrameTime();

		UpdateAnimation(*_scoreText);
		UpdateAnimation(*_scoreTextShadow);

		if (_timeDisplayed > Internal::MAX_SECONDS_DISPLAYED)
		{
			_timeDisplayed = 0.0;
			Hide();
		}
	}
}