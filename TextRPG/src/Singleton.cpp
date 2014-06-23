#ifndef SINGLETON_CPP
#define SINGLETON_CPP

#include "Singleton.h"

// Initialize the instance as NULL
template <typename T> T* Singleton<T>::pInstance = 0;

template <typename T>
void Singleton<T>::CreateInstance()
{
    // Create the instance using its default constructor
	pInstance = new T();
}

template <typename T>
T* Singleton<T>::GetInstance()
{
	if (pInstance == 0)
		CreateInstance();

	return pInstance;
}

template <typename T>
void Singleton<T>::DeleteInstance()
{
	delete T;
}

#endif