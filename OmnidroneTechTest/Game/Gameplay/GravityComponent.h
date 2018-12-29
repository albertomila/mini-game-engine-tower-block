#pragma once
#include <SFML/Graphics/Text.hpp>
#include <Engine/EntityComponent/BaseComponent.h>

class CGameObject;

class CGravityComponent : public CBaseComponent
{
public:
	CGravityComponent(CGameObject& object);

	void Update() override;
	void SetEnable(bool enable);

private:
	bool _isEnabled = false;
	double _simulationDt = 0.0;
};
