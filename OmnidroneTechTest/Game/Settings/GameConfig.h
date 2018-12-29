#pragma once
#include <Engine/Serialization/ISerializable.h>
#include <Engine/Systems/ScreenDescriptor.h>

class CGameConfig : public CSerializableObject
{
public:
	void OnLoad(pugi::xml_node& node) override;
	int GetLives() const { return _lives; }
	float GetTowerStartZPos() const { return _towerStartZPos; }

	const SObjectDescriptor& GetTowerBlockDescriptor() const { return  _towerBlockDescriptor; }
private:
	int _lives = 0;
	float _towerStartZPos = 0.f;
	SObjectDescriptor _towerBlockDescriptor;
};