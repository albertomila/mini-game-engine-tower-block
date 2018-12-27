#include "stdafx.h"
#include <Engine/Systems/IScreen.h>

#include <Engine/Systems/ScreenDescriptor.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Engine/Systems/MainRenderer.h>
#include <Engine/Systems/SystemManager.h>
#include <Engine/Core/StringID.h>
#include <Engine/EntityComponent/BaseObject.h>
#include <Engine/UI/ButtonObject.h>
#include <Engine/Systems/MainWindow.h>

CScreenBase::CScreenBase(const std::string& fileName)
{
	Load(fileName);
}

void CScreenBase::Load(const std::string& fileName)
{
	SScreenDescriptor screenDescriptor;
	screenDescriptor.Load(fileName);

	_screenObjects.reserve(screenDescriptor._objects.size());
	for (const SObjectDescriptor& screenObjectDescriptor : screenDescriptor._objects)
	{
		sf::IntRect textureRect(static_cast<int>(0),
			static_cast<int>(0),
			static_cast<int>(screenObjectDescriptor._width),
			static_cast<int>(screenObjectDescriptor._height));

		if (screenObjectDescriptor._type == SObjectDescriptor::EType::Button)
		{
			_screenObjects.emplace_back(std::make_unique<CButtonObject>(CStringID(screenObjectDescriptor._id.c_str())));
		}
		else if(screenObjectDescriptor._type == SObjectDescriptor::EType::Texture)
		{
			_screenObjects.emplace_back(std::make_unique<CBaseObject>(CStringID(screenObjectDescriptor._id.c_str())));
		}

		std::unique_ptr<IObject>& gameObject = _screenObjects.back();
		gameObject->GetTransform().setPosition(screenObjectDescriptor._x, screenObjectDescriptor._y);
		gameObject->SetZPos(screenObjectDescriptor._z);
		gameObject->SetAlpha(screenObjectDescriptor._alpha);
		gameObject->LoadFromFile(screenObjectDescriptor._texture, textureRect);
	}
}

void CScreenBase::Update()
{
	CMainWindow* mainWindow = CSystemManager::Get().GetSystem<CMainWindow>();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i localMousePosition = sf::Mouse::getPosition(mainWindow->GerRenderWindow());

		for (std::unique_ptr<IObject>& screenObject : _screenObjects)
		{
			const sf::FloatRect& rect = screenObject->GetRect();
			const bool objectPressed = rect.contains(static_cast<float>(localMousePosition.x), static_cast<float>(localMousePosition.x));
			if (objectPressed)
			{
				screenObject->OnPressed();
			}
		}
	}

	CMainRenderer* mainRenderer = CSystemManager::Get().GetSystem<CMainRenderer>();
	for (std::unique_ptr<IObject>& screenObject : _screenObjects)
	{
		mainRenderer->RequestRender(*screenObject);
	}
}