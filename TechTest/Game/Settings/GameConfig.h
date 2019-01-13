#pragma once
#include <Engine/Serialization/ISerializable.h>
#include <Engine/Systems/ScreenDescriptor.h>


struct STowerBlockScoreDescriptor : public CSerializableObject
{
	void OnLoad(pugi::xml_node& node) override;

	int _maxPoints = 0;
	int _perfectPoints = 0;
	float _goodStackAccuracy = 0.f;
	float _perfectStackAccuracy = 0.f;
	std::string _messageFail;
	std::string _messageGood;
	std::string _messagePerfect;
};

class CGameConfig : public CSerializableObject
{
public:
	void OnLoad(pugi::xml_node& node) override;
	int GetLives() const { return _lives; }
	float GetTowerStartZPos() const { return _towerStartZPos; }

	const SObjectDescriptor& GetTowerBlockDescriptor() const { return  _towerBlockDescriptor; }
	const STowerBlockScoreDescriptor& GetTowerBlockScoreDescriptor() const { return _towerBlockScoreDescriptor; }
private:
	int _lives = 0;
	float _towerStartZPos = 0.f;
	SObjectDescriptor _towerBlockDescriptor;
	STowerBlockScoreDescriptor _towerBlockScoreDescriptor;
};