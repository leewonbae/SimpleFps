#pragma once
#include "Resource.h"
#include "cIOCPhandler.h"



class cInitServer : public cSingleton<cInitServer>
{
	friend class cSingleton<cInitServer>;
public:
	void SetInitServer();
	SOCKET GetSocket() const { return mListenSocket; }
private:
	cInitServer();
	virtual ~cInitServer();

	SOCKET mListenSocket;
};

