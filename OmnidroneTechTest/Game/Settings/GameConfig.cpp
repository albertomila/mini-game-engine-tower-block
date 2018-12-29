#include "stdafx.h"
#include <Game/Settings/GameConfig.h>

void CGameConfig::OnLoad(pugi::xml_node& node)
{
	SERIALIZE(node, "lives", _lives);
	SERIALIZE(node, "towerStartZPos", _towerStartZPos);
	SERIALIZE(node, "TowerBlockDescriptor", _towerBlockDescriptor);
	SERIALIZE(node, "TowerBlockScore", _towerBlockScoreDescriptor);
}

void STowerBlockScoreDescriptor::OnLoad(pugi::xml_node& node)
{
	SERIALIZE(node, "maxPoints", _maxPoints);
	SERIALIZE(node, "perfectPoints", _perfectPoints);
	SERIALIZE(node, "goodStackAccuracy", _goodStackAccuracy);
	SERIALIZE(node, "perfectStackAccuracy", _perfectStackAccuracy);
	SERIALIZE(node, "messageFail", _messageFail);
	SERIALIZE(node, "messageGood", _messageGood);
	SERIALIZE(node, "messagePerfect", _messagePerfect);
}
