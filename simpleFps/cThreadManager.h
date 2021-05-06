#pragma once
#include "Resource.h"
#include "cUser.h"
#include "cIOCPhandler.h"
#include "cSynchronization.h"

struct COMPLETION_DATA {
	int mTransByte = 0;
	LPVOID mSessionPtr;

};

class cThreadManager : public cSingleton<cThreadManager>
{
	friend class cSingleton<cThreadManager>;
public:
	void MakeWorkerThreadPool(int _make_count);
 
	static DWORD WINAPI WorkerThread(LPVOID arg);
private:
	cThreadManager();
	~cThreadManager();

	cCriticalSection mCS_MessageLock;
	 
	HANDLE mMakeThreadhandle;
	SYSTEM_INFO mSystemInfo;
	 

};

