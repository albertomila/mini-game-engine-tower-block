#pragma once
#include <Engine/Serialization/ISerializable.h>
#include <SFML/Graphics/Font.hpp>

class CAppConfig : public CSerializableObject
{
public:
	void OnLoad(pugi::xml_node& node) override;

	const std::string& GetPathGameConfig() const;
	const std::string& GetPathSaveData() const;
	const sf::Font& GetGlobalFont() const { return _globalFont; }
	
private:
	std::string _pathGameConfig;
	std::string _pathSaveData;
	sf::Font _globalFont;
};