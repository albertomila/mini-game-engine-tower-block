#include "stdafx.h"
#include <Engine/EntityComponent/GameObject.h>
#include <Engine\EntityComponent\ILocalTransformComponent.h>

CGameObject::CGameObject(const CStringID& id)
	: _id(id)
{
}

void CGameObject::SetPosition(const sf::Vector2f& position)
{
	_transform.setPosition(position);

	std::vector<std::reference_wrapper<ILocalTransformComponent>> drawableComponents = CGameObject::GetComponents<ILocalTransformComponent>();
	for (auto& drawableComponent : drawableComponents)
	{
		drawableComponent.get().UpdatePositionFromParent();
	}
}

void CGameObject::Update()
{
	for (const TComponentPair& componentPair : _components)
	{
		componentPair.second.get()->Update();
	}
}

