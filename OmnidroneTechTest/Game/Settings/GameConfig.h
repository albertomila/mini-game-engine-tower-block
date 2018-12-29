#pragma once
#include <Engine/Serialization/ISerializable.h>
#include <Engine/Systems/ScreenDescriptor.h>

class CGameConfig : public CSerializableObject
{
public:
	void OnLoad(pugi::xml_node& node) override;
	int GetLives() const { return _lives; }
	float GetTowerStartZPos() const { return _towerStartZPos; }
	int GetMaxPoints() const { return _maxPoints; }
	int GetPerfectPoints() const { return _perfectPoints; }
	float GetPerfectStackAccuracy() const { return _perfectStackAccuracy; }

	const SObjectDescriptor& GetTowerBlockDescriptor() const { return  _towerBlockDescriptor; }
private:
	int _lives = 0;
	float _towerStartZPos = 0.f;
	int _maxPoints = 0;
	int _perfectPoints = 0;
	float _perfectStackAccuracy = 0.f;
	SObjectDescriptor _towerBlockDescriptor;
};