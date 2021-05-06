#include "cUser.h"
cUser::cUser() :mUserKey(-1), mUserRemainHp(0)
{
	mMap.insert(make_pair(PROTOCOL_START_REQ, &cUser::START_FUNC));
	mMap.insert(make_pair(PROTOCOL_MOVE_REQ, &cUser::MOVE_FUNC));
	mMap.insert(make_pair(PROTOCOL_ROTATE_REQ, &cUser::ROTATE_FUNC));
	mMap.insert(make_pair(PROTOCOL_SHOOTING_REQ, &cUser::SHOOTING_FUNC));
	mMap.insert(make_pair(PROTOCOL_DAMAGE_REQ, &cUser::DAMAGE_FUNC));
}
cUser::~cUser()
{

}
void cUser::PacketParsing(PACKET_HEAD* _packet)
{
	map<int, pf>::iterator iter;
	iter = mMap.find(_packet->mCmd);

	if (iter != mMap.end())
	{
		pf temp = iter->second;
		(this->*temp)(_packet);

	 
	}
	else
	{
		printf("PACKET PARSING ERROR \n");
	}
}

void cUser::START_FUNC(PACKET_HEAD* _packet)
{
	
	printf("START_FUNC\n");

	mUserRemainHp = 10;
	PACKET_START_REQ* recvpacket = (PACKET_START_REQ*)_packet;
	
	memcpy(&mUserPostion, &recvpacket->mStartPosition, sizeof(POSITION));
	mUserPostion.mSessionNum = this->GetSessionNum();


	cout << mUserPostion.mUserX << endl;
	cout << mUserPostion.mUserY << endl;
	cout << mUserPostion.mUserZ << endl;
 
	SINGLETON(cUserManager).InputStartPosition(&mUserPostion,(cSession*)this);


}
 

void cUser::MOVE_FUNC(PACKET_HEAD* _packet)
{
	printf("MOVE_FUNC\n");
	PACKET_MOVE_REQ* recvpacket = (PACKET_MOVE_REQ*)_packet;


	mUserPostion.mUserX = recvpacket->mPositionInfo_req.mUserX;
	mUserPostion.mUserY = recvpacket->mPositionInfo_req.mUserY;
	mUserPostion.mUserZ = recvpacket->mPositionInfo_req.mUserZ;
 
	SINGLETON(cUserManager).UpdatePosition(this, &mUserPostion);
 
}


void cUser::ROTATE_FUNC(PACKET_HEAD* _packet)
{
	printf("ROTATE_FUNC\n");
	PACKET_ROTATE_REQ* recvpacket = (PACKET_ROTATE_REQ*)_packet;

	cout << "recv = rotate ===" << recvpacket->mRotate << endl;
	SINGLETON(cUserManager).RotateSendPacket(this, recvpacket->mRotate);
 
}
void cUser::SHOOTING_FUNC(PACKET_HEAD* _packet)
{
	printf("SHOOTING_FUNC\n");
	SINGLETON(cUserManager).ShootingReq(this);
}
void cUser::DAMAGE_FUNC(PACKET_HEAD* _packet)
{
	printf("DAMAGE_FUNC\n");
	PACKET_DAMAGE_REQ* recvpacket = (PACKET_DAMAGE_REQ*)_packet;
	 
	SINGLETON(cUserManager).DamageReq(this, recvpacket->mRemainHp);
}
