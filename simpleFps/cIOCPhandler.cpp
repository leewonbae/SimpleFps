#include "cIOCPhandler.h"
cIOCPhandler::cIOCPhandler()
{

	mIOCPhandler = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
}
cIOCPhandler::~cIOCPhandler()
{

}

void cIOCPhandler::SetMakeListenCP(SOCKET _listensock)
{
	mIOCPhandler = CreateIoCompletionPort((HANDLE)_listensock, mIOCPhandler, NULL, 0);
}

void cIOCPhandler::SetMakeSessionCP(cSession* _session)
{
	cSynchronization sync(mCS_IOCP);

	mIOCPhandler = CreateIoCompletionPort((HANDLE)_session->GetSessionSock(),
		mIOCPhandler,
		(ULONG_PTR)_session,
		0);
}