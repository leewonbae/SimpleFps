
#include "cInitServer.h"
#include "cIOCPhandler.h"
#include "cSessionManager.h"
#include "cThreadManager.h"

#define MAX_SESSION_COUNT 20

int main()
{

	SINGLETON(cInitServer).SetInitServer();
	SINGLETON(cSessionManager).MakeSessionPool(MAX_SESSION_COUNT);
	SINGLETON(cThreadManager).MakeWorkerThreadPool(0);
	getchar();
	getchar();
	return 0;
}