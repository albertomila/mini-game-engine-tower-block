#pragma once

class CGameObject;

class IObjectComponent {
public:
	using Id = size_t;
	
	template<class T>
	static Id GetComponentId() {
		return typeid(T).hash_code();
	}

	virtual const CGameObject& GetObject() const = 0;
	virtual	CGameObject& GetObject() = 0;
};
