#pragma once
#include <Engine/Serialization/ISerializable.h>
#include <SFML/Graphics/Font.hpp>

class CAppConfig : public CSerializableObject
{
public:
	void OnLoad(pugi::xml_node& node) override;

	const std::string& GetPathGameConfig() const { return _pathGameConfig; }
	const std::string& GetPathSaveData() const { return _pathSaveData; }
	const sf::Font& GetGlobalFont() const { return _globalFont; }
	int GetWindowWidth() const { return _windowWidth; }
	int GetWindowHeight() const { return _windowHeight; }
	const std::string& GetWindowTitle() const { return _windowTitle; }

private:
	std::string _pathGameConfig;
	std::string _pathSaveData;
	sf::Font _globalFont;
	int _windowWidth = 0;
	int _windowHeight = 0;
	std::string _windowTitle;
};