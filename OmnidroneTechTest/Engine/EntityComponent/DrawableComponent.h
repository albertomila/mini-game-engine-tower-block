#pragma once
#include <Engine\EntityComponent\BaseComponent.h>
#include <SFML\Graphics\Drawable.hpp>

class CGameObject;

class CDrawableComponent : public CBaseComponent {
public:
	CDrawableComponent(CGameObject& object)
		: CBaseComponent(object)
	{
	}

	virtual sf::Drawable& GetDrawable() = 0;
};