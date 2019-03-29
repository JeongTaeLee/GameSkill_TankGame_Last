#pragma once

template <class T>
class singleton
{
private:
	static T * pMar;

public:
	singleton(){}
	virtual ~singleton(){}

	static T * Getinst()
	{
		if (!pMar)
			pMar = new T;

		return pMar;
	}

	static void ReleaseInst()
	{
		if (pMar)
			delete pMar;

		pMar = nullptr;
	}
};

template <class T>
T * singleton<T>::pMar = nullptr;