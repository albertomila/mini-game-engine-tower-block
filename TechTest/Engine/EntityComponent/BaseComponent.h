#pragma once
#include <Engine\EntityComponent\IObjectComponent.h>

class CGameObject;

class CBaseComponent : public IObjectComponent {
public:
	CBaseComponent(CGameObject& object)
		: _object(object)
	{
	}

	const CGameObject& GetObject() const override { return _object; }
	CGameObject& GetObject() override { return _object; }

private:
	CGameObject& _object;
};