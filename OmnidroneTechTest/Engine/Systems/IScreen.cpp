#include "stdafx.h"
#include <Engine/Systems/IScreen.h>

#include <Engine/Systems/ScreenDescriptor.h>
#include <Engine/Systems/MainRenderer.h>
#include <Engine/Systems/SystemManager.h>
#include <Engine/Core/StringID.h>
#include <Engine/EntityComponent/GameObject.h>
#include <Engine/Systems/MainWindow.h>
#include <Engine/UI/TextComponent.h>
#include <Engine/UI/ButtonComponent.h>
#include <Engine/UI/SpriteComponent.h>

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
		CGameObject* baseObject = new CGameObject(CStringID(screenObjectDescriptor._id.c_str()));

		if (   screenObjectDescriptor._type == SObjectDescriptor::EType::Texture 
			|| screenObjectDescriptor._type == SObjectDescriptor::EType::Button)
		{
			sf::IntRect textureRect(static_cast<int>(0),
				static_cast<int>(0),
				static_cast<int>(screenObjectDescriptor._width),
				static_cast<int>(screenObjectDescriptor._height));

			CSpriteComponent& spriteComponent = baseObject->RegisterComponent<CSpriteComponent>(*baseObject);
			spriteComponent.LoadFromFile(screenObjectDescriptor._texture, textureRect);
			spriteComponent.SetAlpha(screenObjectDescriptor._alpha);
		}

		if (   screenObjectDescriptor._type == SObjectDescriptor::EType::Text
			|| screenObjectDescriptor._type == SObjectDescriptor::EType::Button)
		{
			const std::string& text = screenObjectDescriptor._text;
			baseObject->RegisterComponent<CTextComponent>(*baseObject, text);
		}

		if (screenObjectDescriptor._type == SObjectDescriptor::EType::Button)
		{
			const std::string& text = screenObjectDescriptor._text;
			baseObject->RegisterComponent<CButtonComponent>(*baseObject);
		}

		baseObject->SetRenderLayer(screenObjectDescriptor._renderLayer);
		baseObject->SetPosition({ screenObjectDescriptor._x, screenObjectDescriptor._y });
		baseObject->SetZPos(screenObjectDescriptor._z);

		_screenObjects.emplace_back(baseObject);
	}
}

void CScreenBase::Update()
{
	CMainWindow* mainWindow = CSystemManager::Get().GetSystem<CMainWindow>();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i localMousePosition = sf::Mouse::getPosition(mainWindow->GerRenderWindow());
		sf::Vector2i mousePosition = sf::Mouse::getPosition();

		for (std::unique_ptr<CGameObject>& screenObject : _screenObjects)
		{
			CSpriteComponent* spriteComponent = screenObject->GetComponent<CSpriteComponent>();
			if (spriteComponent)
			{
				const sf::FloatRect& rect = spriteComponent->GetRect();
				const bool objectPressed = rect.contains(static_cast<float>(localMousePosition.x), static_cast<float>(localMousePosition.y));
				if (objectPressed)
				{
					CButtonComponent* buttonComponent = screenObject->GetComponent<CButtonComponent>();
					if (buttonComponent)
					{
						buttonComponent->OnPressed();
					}
				}
			}
		}
	}

	CMainRenderer* mainRenderer = CSystemManager::Get().GetSystem<CMainRenderer>();
	for (std::unique_ptr<CGameObject>& screenObject : _screenObjects)
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
	using TObjectList = std::vector<std::unique_ptr<CGameObject>>;
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
	for (std::unique_ptr<CGameObject>& screenObject : _screenObjects)
	{
		screenObject->SetEnabled(visible);
	}
}
