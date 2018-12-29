#include "stdafx.h"
#include <Game/Gameplay/GravityComponent.h>
#include <Engine/Core/GameTimer.h>
#include <Engine/EntityComponent/GameObject.h>

namespace Internal 
{
	const float SPEED_FACTOR = 5.0f;
	const float GRAVITY_FACTOR = 9.81f;
}

CGravityComponent::CGravityComponent(CGameObject& object)
	: CBaseComponent(object)
{
}

void CGravityComponent::Update()
{
	if (_isEnabled) 
	{
		_simulationDt += CGameTimer::Get().GetFrameTime();

		sf::Vector2f position = GetObject().GetTransform().getPosition();
		position.y += Internal::SPEED_FACTOR * Internal::GRAVITY_FACTOR * pow(_simulationDt, 2);
		GetObject().SetPosition(position);
	}
}

void CGravityComponent::SetEnable(bool enable)
{
	_isEnabled = enable;
}

