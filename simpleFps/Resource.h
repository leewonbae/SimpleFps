#pragma once
#include <iostream>
#include <WinSock2.h>
#include <mswsock.h>
#include <map>
#include <vector>
#include <queue>
#include <list>
 
#include <string>
using namespace std;
//////////////////////////////////////////////////////////////////////////
#pragma comment (lib,"ws2_32.lib")
#pragma comment (lib,"mswsock.lib")
 
//////////////////////////////////////////////////////////////////////////

#include "cSingleton.h"

//////////////////////////////////////////////////////////////////////////
#define PORT 7296
#define BUFFER_SIZE 1024


#define DB_ID "root"
#define DB_HOST "127.0.0.1"
#define DB_NAME "scema_chatting_server"
#define DB_PASSWORD "814dnjsqo*"
#define DB_PORT 3306

//////////////////////////////////////////////////////////////////////////
enum WORK_FLEG {
	FLEG = 0,
	FLEG_ACCEPT,
	FLEG_RECV,
	FLEG_SEND,
};

//////////////////////////////////////////////////////////////////////////
struct OVERDATA {

	OVERLAPPED mOverlapped;
	int mWorkFleg = FLEG;
	WSABUF mWsabuf;
	LPVOID SelfPoint;
};