#pragma once
#include <Engine/Serialization/ISerializable.h>

class CGameConfig : public CSerializableObject
{
public:
	void OnLoad(pugi::xml_node& node) override;
};