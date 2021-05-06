#pragma once
#include "Resource.h"
#include "cSynchronization.h"
#include "cUser.h"

class cSession;
class cIOCPhandler : public cSingleton<cIOCPhandler>
{
	friend class cSingleton<cIOCPhandler>;
public:
	void SetMakeSessionCP(cSession* _session);
	void SetMakeListenCP(SOCKET _listensock);


	HANDLE GetIOCPhandler() const { return mIOCPhandler; }

private:
	cIOCPhandler();
	virtual ~cIOCPhandler();

	cCriticalSection mCS_IOCP;
	HANDLE mIOCPhandler;
};

