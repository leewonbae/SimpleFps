#pragma once
#include "Resource.h"
class cCriticalSection
{
public:
	cCriticalSection();
	~cCriticalSection();

	void LockCS();
	void UnlockCS();
private:
	CRITICAL_SECTION mCS;

};


class cSynchronization
{
public:
	cSynchronization(cCriticalSection& _cs);
	~cSynchronization();

private:
	cCriticalSection* mCS;
};

