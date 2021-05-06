#pragma once
#include "Resource.h"
#include "cUser.h"
#include "cSynchronization.h"
class cSessionManager : public cSingleton<cSessionManager>
{
	friend class cSingleton<cSessionManager>;
public:
	void MakeSessionPool(int _make_count);
	void InputSession();
	void OutputSession();
private:
	cSessionManager();
	virtual ~cSessionManager();


	map<int, cSession*> mSessionMap;
	cCriticalSection mCS_SessionManager;
	int mSessionCount;
};

