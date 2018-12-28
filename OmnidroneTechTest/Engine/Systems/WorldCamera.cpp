#include "stdafx.h"
#include <Engine/Systems/WorldCamera.h>

CWorldCamera::CWorldCamera(float cameraPosX, float cameraPosY)
{
	_defaultPosition.x = cameraPosX;
	_defaultPosition.y = cameraPosY;
	_position = _defaultPosition;
}

void CWorldCamera::Init()
{
	_position = _defaultPosition;
}

void CWorldCamera::Move(float x, float y)
{
	SetPosition(_position.x + x, _position.y + y);
}

void CWorldCamera::MoveX(float x)
{
	SetPosition(_position.x + x, _position.y);
}

void CWorldCamera::MoveY(float y)
{
	SetPosition(_position.x, _position.y + y);
}

void CWorldCamera::SetPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
}
