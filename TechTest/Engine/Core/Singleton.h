#pragma once

template<typename T>
class CSingleton
{
public:
	static void CreateInstance();
	static void DestroyInstance();
	static inline T& Get();

protected:
	CSingleton(){}
	~CSingleton() = default;

private:
	CSingleton(const CSingleton&){}
	void operator=(const CSingleton&){}

private:
	static T* s_instance;
};

template<typename T>
T* CSingleton<T>::s_instance = nullptr;

template<typename T>
void CSingleton<T>::CreateInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new T();
	}
	else
	{
		assert(false && "instance already created");
	}
}

template<typename T>
void CSingleton<T>::DestroyInstance()
{
	delete s_instance;
	s_instance = nullptr;
}

template<typename T>
inline T& CSingleton<T>::Get()
{
	return *s_instance;
}