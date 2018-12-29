#include "stdafx.h"
#include <Engine/Systems/ScrollParallaxController.h>
#include <Engine/Systems/WorldCamera.h>
#include <Engine/Systems/SystemManager.h>

void CParallaxController::Init(float windowHeightCenter)
{
	_windowHeightCenter = windowHeightCenter;
	_worldCamera = CSystemManager::Get().GetSystem<CWorldCamera>();
}

void CParallaxController::Clear()
{
	_parallaxObjects.clear();
}

void CParallaxController::AddObject(CGameObject& object, float parallaxFactor)
{
	_parallaxObjects.emplace_back(SParallaxObjectPair{ std::ref(object), parallaxFactor });
}

void CParallaxController::Update()
{
	const sf::Vector2f& cameraPosition = _worldCamera->GetPosition();

	for (SParallaxObjectPair& parallaxObject : _parallaxObjects)
	{
		const sf::Transformable& objectTransform = parallaxObject._object.get().GetTransform();

		const sf::Vector2f& objectPositionRef = objectTransform.getPosition();
		sf::Vector2f objectPosition = objectTransform.getPosition();
		parallaxObject._absoluteWorldPosition = objectPosition;

		float y = objectPosition.y + _windowHeightCenter - cameraPosition.y;
		y *= parallaxObject.parallaxFactor;

		objectPosition.y = y;
		parallaxObject._object.get().SetPosition(objectPosition);
	}
}

void CParallaxController::RevertParallaxTranslation()
{
	for (SParallaxObjectPair& parallaxObject : _parallaxObjects)
	{
		CGameObject& gameObject = parallaxObject._object.get();
		const sf::Transformable& objectTransform = gameObject.GetTransform();
		gameObject.SetPosition(parallaxObject._absoluteWorldPosition);
	}
}
