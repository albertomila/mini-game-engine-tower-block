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
#include <Engine/UI/TextObject.h>

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
			const std::string& text = screenObjectDescriptor._text;
			_screenObjects.emplace_back(std::make_unique<CButtonObject>(CStringID(screenObjectDescriptor._id.c_str()), text));
		}
		else if(screenObjectDescriptor._type == SObjectDescriptor::EType::Texture)
		{
			_screenObjects.emplace_back(std::make_unique<CBaseObject>(CStringID(screenObjectDescriptor._id.c_str())));
		}
		else if (screenObjectDescriptor._type == SObjectDescriptor::EType::Text)
		{
			const std::string& text = screenObjectDescriptor._text;
			_screenObjects.emplace_back(std::make_unique<CTextObject>(CStringID(screenObjectDescriptor._id.c_str()), text));
		}

		std::unique_ptr<IObject>& gameObject = _screenObjects.back();
		gameObject->SetRenderLayer(screenObjectDescriptor._renderLayer);
		gameObject->GetTransform().setPosition(screenObjectDescriptor._x, screenObjectDescriptor._y);
		gameObject->SetZPos(screenObjectDescriptor._z);
		gameObject->SetAlpha(screenObjectDescriptor._alpha);

		if (!screenObjectDescriptor._texture.empty())
		{
			gameObject->LoadFromFile(screenObjectDescriptor._texture, textureRect);
		}
	}
}

void CScreenBase::Update()
{
	CMainWindow* mainWindow = CSystemManager::Get().GetSystem<CMainWindow>();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i localMousePosition = sf::Mouse::getPosition(mainWindow->GerRenderWindow());
		sf::Vector2i mousePosition = sf::Mouse::getPosition();

		for (std::unique_ptr<IObject>& screenObject : _screenObjects)
		{
			const sf::FloatRect& rect = screenObject->GetRect();
			const bool objectPressed = rect.contains(static_cast<float>(localMousePosition.x), static_cast<float>(localMousePosition.y));
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

void CScreenBase::Show()
{
	SetVisible(true);
}

void CScreenBase::Hide()
{
	SetVisible(false);
}

void CScreenBase::RemoveObject(const CStringID& objectId)
{
	using TObjectList = std::vector<std::unique_ptr<IObject>>;
	using TObjectIt = TObjectList::iterator;
	for (TObjectIt it = std::begin(_screenObjects); it != std::end(_screenObjects);)
	{
		if (it->get()->GetId() == objectId)
		{
			it = _screenObjects.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}
}

void CScreenBase::SetVisible(bool visible)
{
	_isVisible = visible;
	for (std::unique_ptr<IObject>& screenObject : _screenObjects)
	{
		screenObject->SetEnabled(visible);
	}
}
