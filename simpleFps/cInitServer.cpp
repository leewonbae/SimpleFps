#include "cInitServer.h"
cInitServer::cInitServer()
{

}
cInitServer::~cInitServer()
{

	closesocket(mListenSocket);
	WSACleanup();
}
void cInitServer::SetInitServer()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	mListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	int check = 0;
	bool opt = true;
	check = setsockopt(mListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
	if (check == SOCKET_ERROR)
	{
		printf("socket option error\n");
		return;
	}
	check = setsockopt(mListenSocket, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, (char*)&opt, sizeof(opt));

	if (check == SOCKET_ERROR)
	{
		printf("socket option error\n");
		return;
	}

	bind(mListenSocket, (sockaddr*)&serveraddr, sizeof(serveraddr));

	listen(mListenSocket, SOMAXCONN);


	SINGLETON(cIOCPhandler).SetMakeListenCP(mListenSocket);

	printf("set init server ok \n");
}