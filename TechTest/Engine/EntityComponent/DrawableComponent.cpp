#include "stdafx.h"
#include <Engine/EntityComponent/DrawableComponent.h>
#include <Engine/EntityComponent/GameObject.h>
#include <Engine/Systems/MainRenderer.h>
#include <Engine/Systems/SystemManager.h>

const sf::Transform& CDrawableComponent::GetTransform()
{
	return GetTransformable().getTransform();
}

void CDrawableComponent::SetLocalPosition(const sf::Vector2f& localposition)
{
	_localTransform.setPosition(localposition);
	UpdatePositionFromParent();
}

void CDrawableComponent::UpdatePositionFromParent()
{
	const sf::Vector2f& parentPosition = GetObject().GetTransform().getPosition();
	GetTransformable().setPosition(parentPosition + _localTransform.getPosition());
}

void CDrawableComponent::Update()
{
	CMainRenderer* mainRenderer = CSystemManager::Get().GetSystem<CMainRenderer>();
	mainRenderer->RequestRender(*this);
}
