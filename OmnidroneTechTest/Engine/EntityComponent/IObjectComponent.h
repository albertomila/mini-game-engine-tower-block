#pragma once
#include <Engine\Core\IUpdatable.h>

class CGameObject;

class IObjectComponent : public IUpdatable {
public:
	using Id = size_t;
	
	template<class T>
	static Id GetComponentId() {
		return typeid(T).hash_code();
	}

	void Init() override {}
	void Update() override {}
	void Shutdown() override {}

	virtual const CGameObject& GetObject() const = 0;
	virtual	CGameObject& GetObject() = 0;
};
