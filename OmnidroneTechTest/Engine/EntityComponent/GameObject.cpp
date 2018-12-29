#include "stdafx.h"
#include <Engine/EntityComponent/GameObject.h>

CGameObject::CGameObject(const CStringID& id)
	: _id(id)
{
}

CGameObject::~CGameObject()
{
	for (const TComponentPair& componentPair : _components)
	{
		delete componentPair.second;
	}
}

