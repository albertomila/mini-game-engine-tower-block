#pragma once
#include <vector>
#include <Engine\EntityComponent\IObject.h>

class CWorldCamera;

class CParallaxController 
{
	struct SParallaxObjectPair
	{
		std::reference_wrapper<IObject> _object;
		float parallaxFactor = 1.0f;
		sf::Vector2f _absoluteWorldPosition;
	};

public:
	void Init(float windowHeightCenter);
	void AddObject(IObject& object, float parallaxFactor);
	void Update();
	void RestoreParallaxTranslation();

private:
	const CWorldCamera* _worldCamera = nullptr;
	std::vector<SParallaxObjectPair> _parallaxObjects;
	float _windowHeightCenter = 0.0f;
};
