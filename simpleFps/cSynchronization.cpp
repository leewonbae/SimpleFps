#include "cSynchronization.h"
cCriticalSection::cCriticalSection()
{
	InitializeCriticalSection(&mCS);
}
cCriticalSection::~cCriticalSection()
{
	DeleteCriticalSection(&mCS);
}
void cCriticalSection::LockCS()
{
	EnterCriticalSection(&mCS);
}
void cCriticalSection::UnlockCS()
{
	LeaveCriticalSection(&mCS);
}

cSynchronization::cSynchronization(cCriticalSection& _cs) : mCS(&_cs)
{

	mCS->LockCS();
}
cSynchronization::~cSynchronization()
{
	mCS->UnlockCS();

}