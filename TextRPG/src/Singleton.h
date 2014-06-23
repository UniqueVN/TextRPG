#pragma once

template <typename T>
class Singleton
{
public:
	static void CreateInstance();
	static T* GetInstance();
	static void DeleteInstance();

private:
	static T* pInstance;
};

#include "Singleton.cpp"