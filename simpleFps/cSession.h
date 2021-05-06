#pragma once
#include "Resource.h"
#include "Packet.h"
 


class cSession
{
public:
	cSession();
	virtual ~cSession();

	SOCKET GetSessionSock() const { return mSessionSock; }

	void SetLogIn(bool _login) { mLoginCheck = _login; }
	bool GetLogin() { return mLoginCheck; }

	void AcceptOn();
	void OnRecv();
	void OnSend(void* _packet, int _packetsize);
	void ClientOut();

	int GetSessionNum() { return mSessionNum; }
	void SetSessionNum(int _num) { mSessionNum = _num; }

	virtual void PacketParsing(PACKET_HEAD* _packet) = 0;

	void RecvProcess(int _transbyte);
	void SendProcess();

private:
	void SetReadyAccept();
	void RecycleCloseSocket();


private:
	OVERDATA mAcceptOverdata, mRecvOverdata, mSendOverdata, mDisConnetOverdata;
	SOCKET mSessionSock;

	char mAcceptBuf[BUFFER_SIZE] = { 0, };
	char mSendBuf[BUFFER_SIZE] = { 0, };
	char mRecvBuf[BUFFER_SIZE] = { 0, };
	
	int mSessionNum;
	bool mLoginCheck;
};

