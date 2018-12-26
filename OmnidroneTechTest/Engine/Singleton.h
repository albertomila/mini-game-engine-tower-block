#pragma once

#include <assert.h>

template<typename T>
class CSingleton
{
public:
	static void CreateInstance()
	{
		if( s_instance == nullptr )
		{
			s_instance = new T();
		}
		else
		{
			assert(false && "instance already created");
		}
	}
	
	static void DestroyInstance()
	{
		delete s_instance;
		s_instance = nullptr;
	}

	static inline T* Get()
	{
		return s_instance;
	}

protected:
	CSingleton(){}
	~CSingleton(){}

private:
	CSingleton(const CSingleton&){}
	void operator=(const CSingleton&){}

private:
	static T* s_instance;
};

template< typename T >
T* CSingleton<T>::s_instance = nullptr;