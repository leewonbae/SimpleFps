#include "cSession.h"
#include "cIOCPhandler.h"
#include "cInitServer.h"
#include "cSessionManager.h"

cSession::cSession() : mLoginCheck(false), mSessionNum(0)
{
	SetReadyAccept();

}
cSession::~cSession()
{

}

//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : recvprocess
//�ۼ��� : �̿���
//��  �� : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cSession::RecvProcess(int _transbyte)
{
	PACKET_HEAD* recvpacket = (PACKET_HEAD*)mRecvBuf;
	PacketParsing(recvpacket);

	OnRecv();
}


//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : Ŭ���̾�Ʈ ����
//�ۼ��� : �̿���
//��  �� : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cSession::ClientOut()
{
	RecycleCloseSocket();
	ZeroMemory(&mRecvOverdata.mOverlapped, sizeof(mRecvOverdata.mOverlapped));
	ZeroMemory(&mSendOverdata.mOverlapped, sizeof(mSendOverdata.mOverlapped));
	 
	mLoginCheck = false;
	SINGLETON(cSessionManager).OutputSession();
}


//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : ���� accept on
//�ۼ��� : �̿���
//��  �� : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cSession::AcceptOn()
{
	SINGLETON(cIOCPhandler).SetMakeSessionCP(this);
	SINGLETON(cSessionManager).InputSession();

	PACKET_ACCEPT_ACK sendpacket;
	sendpacket.mMySessionNum = mSessionNum;
	cout << "msessionnum ===" << mSessionNum << endl;
	this->OnSend(&sendpacket, sizeof(PACKET_ACCEPT_ACK));

	OnRecv();
}

//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : ���� recv �غ�
//�ۼ��� : �̿���
//��  �� : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------


void cSession::OnRecv()
{

	DWORD recvbytes, flag = 0;
 

	ZeroMemory(&mRecvOverdata.mOverlapped, sizeof(mRecvOverdata.mOverlapped));

	mRecvOverdata.mWsabuf.buf = mRecvBuf;
	mRecvOverdata.mWsabuf.len = BUFFER_SIZE;

	mRecvOverdata.mWorkFleg = FLEG_RECV;
	WSARecv(mSessionSock, &mRecvOverdata.mWsabuf, 1, &recvbytes, &flag, &mRecvOverdata.mOverlapped, NULL);



}

//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : ���� send ��Ŷ
//�ۼ��� : �̿���
//��  �� : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cSession::OnSend(void* _packet, int _packetsize)
{
	DWORD sendbytes;
	mSendOverdata.mWorkFleg = FLEG_SEND;

	ZeroMemory(&mSendOverdata.mOverlapped, sizeof(mSendOverdata.mOverlapped));
	//mSendBuf.Enqueue(_packet, _packetsize);

	//char buf[BUFFER_SIZE] = { 0, };
	memcpy(mSendBuf, _packet, _packetsize);

	mSendOverdata.mWsabuf.buf = (char*)mSendBuf;
	mSendOverdata.mWsabuf.len = _packetsize;


	int retval = WSASend(mSessionSock, &mSendOverdata.mWsabuf, 1, &sendbytes, 0, &mSendOverdata.mOverlapped, NULL);
	if (retval == 0)
	{

		//mSendBuf.Dequeue(_packetsize);
		// �ѹ��� ����
		// �ٷ� ��ť
	}
	else if (retval == SOCKET_ERROR && WSAGetLastError() == ERROR_IO_PENDING)
	{

		//��ø���� ����
	}
	else
	{
		// �̰͵� ���͵� �ƴ� ���� ����
	}



}
//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : ���� Ǯ�� �غ� 
//�ۼ��� : �̿���
//��  �� : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
void cSession::SetReadyAccept()
{

	ZeroMemory(&mAcceptOverdata.mOverlapped, sizeof(mAcceptOverdata.mOverlapped));
	mAcceptOverdata.mWorkFleg = FLEG_ACCEPT;
	mAcceptOverdata.mWsabuf.buf = mAcceptBuf;
	mAcceptOverdata.SelfPoint = this;

	SOCKET ListenSock = SINGLETON(cInitServer).GetSocket();
	if (ListenSock == INVALID_SOCKET)
	{
		cout << "session get sock error" << endl;
	}
	mSessionSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mSessionSock == INVALID_SOCKET)
	{
		cout << "session get sock error" << endl;
	}

	DWORD recvbytes = 0;


	setsockopt(mSessionSock, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char*)&ListenSock, sizeof(ListenSock));

	DWORD retval = AcceptEx(ListenSock, mSessionSock, mAcceptOverdata.mWsabuf.buf, 0, sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16, &recvbytes, (LPOVERLAPPED)&mAcceptOverdata.mOverlapped);


	if (retval == false && WSAGetLastError() != WSA_IO_PENDING)
	{
		printf("AcceptEx Fail\n");
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
//��  �� : ���� ��Ȱ��
//�ۼ��� : �̿���
//��  �� : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

void cSession::RecycleCloseSocket()
{
	TransmitFile(mSessionSock, NULL, NULL, NULL, (LPOVERLAPPED)&mDisConnetOverdata, NULL, TF_DISCONNECT | TF_REUSE_SOCKET);
	SetReadyAccept();
}

 