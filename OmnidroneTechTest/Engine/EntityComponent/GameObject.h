#pragma once
#include <Engine/EntityComponent/RenderLayer.h>
#include <Engine/EntityComponent/IObjectComponent.h>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>
#include <map>

class CGameObject final
{
public:
	CGameObject(const CStringID& id);
	const CStringID& GetId() const { return _id; }
	const sf::Transformable& GetTransform() const { return _transform; }
	void SetPosition(const sf::Vector2f& position);

	void SetZPos(float z) { _z = z; }
	float GetZPos() const { return _z; }
	void SetEnabled(bool enabled) { _enabled = enabled; }
	bool IsEnabled() const { return _enabled; }

	void SetRenderLayer(RenderLayer::ERenderLayer renderLayer) { _renderLayer = renderLayer; }
	RenderLayer::ERenderLayer GetRenderLayer() const { return _renderLayer; }

	template<class T, class ...TArgs>
	T& RegisterComponent(TArgs&... args);

	template<class T>
	std::vector<std::reference_wrapper<T>> GetComponents() const;

	template<class T>
	T* GetComponent();

private:
	CStringID _id;
	sf::Transformable _transform;
	float _z = 0.0f;
	bool _enabled = true;
	RenderLayer::ERenderLayer _renderLayer = RenderLayer::ERenderLayer::World;

	using TComponentPair = std::pair<const IObjectComponent::Id, std::unique_ptr<IObjectComponent>>;
	std::map<IObjectComponent::Id, std::unique_ptr<IObjectComponent>> _components;
};

template<class T, class ...TArgs>
T& CGameObject::RegisterComponent(TArgs&... args)
{
	T* newComponent = new T(*this, args...);
	_components.emplace(IObjectComponent::GetComponentId<T>(), newComponent);
	return *newComponent;
}

template<class TComponent>
TComponent* CGameObject::GetComponent()
{
	const IObjectComponent::Id componentId = IObjectComponent::GetComponentId<TComponent>();
	auto it = _components.find(componentId);
	if (it != _components.end()) {
		IObjectComponent* component = it->second.get();
		return dynamic_cast<TComponent*>(component);
	}

	return nullptr;
}

template<class T>
std::vector<std::reference_wrapper<T>> CGameObject::GetComponents() const
{
	std::vector<std::reference_wrapper<T>> components;
	for (const TComponentPair& componentPair : _components) 
	{
		T* componentCasted = dynamic_cast<T*>(componentPair.second.get());
		if (componentCasted)
		{
			components.push_back(std::ref(*componentCasted));
		}
	}

	return components;
}
