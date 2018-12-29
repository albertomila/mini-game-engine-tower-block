#pragma once
#include <vector>
#include <Engine\EntityComponent\GameObject.h>

class CWorldCamera;

class CParallaxController 
{
	struct SParallaxObjectPair
	{
		std::reference_wrapper<CGameObject> _object;
		float parallaxFactor = 1.0f;
		sf::Vector2f _absoluteWorldPosition;
	};

public:
	void Init(float windowHeightCenter);
	void AddObject(CGameObject& object, float parallaxFactor);
	void Update();
	void RevertParallaxTranslation();

private:
	const CWorldCamera* _worldCamera = nullptr;
	std::vector<SParallaxObjectPair> _parallaxObjects;
	float _windowHeightCenter = 0.0f;
};
