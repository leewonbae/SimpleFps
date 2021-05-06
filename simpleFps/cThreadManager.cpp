#include "cThreadManager.h"
cThreadManager::cThreadManager() 
{
	mMakeThreadhandle = CreateEvent(NULL, true, false, NULL);
	GetSystemInfo(&mSystemInfo);
}
cThreadManager::~cThreadManager()
{

}
void cThreadManager::MakeWorkerThreadPool(int _make_count)
{
	int make_thread = 0;
	if (_make_count == 0)
	{
		make_thread = static_cast<int>(mSystemInfo.dwNumberOfProcessors);

	}
	else
	{
		make_thread = _make_count;
	}

	 

	for (int i = 0;i < make_thread * 2;i++)
	{
		CreateThread(NULL, 0, WorkerThread, this, 0, NULL);
		WaitForSingleObject(mMakeThreadhandle, INFINITE);

	}

	printf("THREAD =  %d 생성 완료\n", make_thread * 2);
}
 
DWORD WINAPI  cThreadManager::WorkerThread(LPVOID arg)
{
	cThreadManager* thread = (cThreadManager*)arg;
	SetEvent(thread->mMakeThreadhandle);
	DWORD transbytes, retval;
	cSession* ptr_session = NULL;
	OVERDATA* ptr_over = NULL;

	while (1)
	{
		retval = GetQueuedCompletionStatus(SINGLETON(cIOCPhandler).GetIOCPhandler(), &transbytes,
			(PULONG_PTR)&ptr_session, (LPOVERLAPPED*)&ptr_over, INFINITE);

		int last_error = WSAGetLastError();


		if (retval == true && transbytes == 0 && ptr_session == NULL)// 클라이언트 접속 처리 
		{

			if (ptr_over->mWorkFleg == FLEG_ACCEPT)
			{
				printf("accept ok\n");
				ptr_session = static_cast<cSession*>(ptr_over->SelfPoint);
				ptr_session->AcceptOn();
			}

		}
		else if (retval == true && transbytes != 0)//작업 분류체크 
		{

			if (ptr_over->mWorkFleg == FLEG_RECV)
			{
				cout << "==========================================" << endl;
				ptr_session->RecvProcess(transbytes);
				 
			}
			if (ptr_over->mWorkFleg == FLEG_SEND)
			{

				
			}

			continue;
		}

		else if (transbytes == 0 && ptr_session != NULL)//  종료
		{
			// 유저라면
			ptr_session->ClientOut();
			printf("클라이언트 접속 해제\n");
		}

	}

	return 0;
}

 