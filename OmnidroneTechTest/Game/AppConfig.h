#pragma once
#include <Engine\Serialization\ISerializable.h>

class CAppConfig : public CSerializableObject
{
public:
	void OnLoad(pugi::xml_node& node) override;

	const std::string& GetPathGameConfig() const
	{
		return _pathGameConfig;
	}

private:
	std::string _pathGameConfig;
};