#pragma once
#include <Engine\Serialization\ISerializable.h>

class CAppConfig : public CSerializableObject
{
public:
	void OnLoad(pugi::xml_node& node) override;

	const std::string& GetPathGameConfig() const;
	const std::string& GetPathSaveData() const;
	
private:
	std::string _pathGameConfig;
	std::string _pathSaveData;
};