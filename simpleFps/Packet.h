#pragma once
#include "Resource.h"
enum PROTOCOL {
	PROTOCOL_PACKET_HEAD = 0,

	PROTOCOL_ACCEPT_ACK,

	PROTOCOL_START_REQ,
	PROTOCOL_MY_START_ACK,   
	PROTOCOL_ENEMY_START_ACK,


	PROTOCOL_MOVE_REQ,
	PROTOCOL_MOVE_ACK, // 나를 제외한 나머지에게 누가 , 어디 포지션으로 바뀌엇는지 전송
 
	PROTOCOL_ROTATE_REQ,
	PROTOCOL_ROTATE_ACK,

	PROTOCOL_SHOOTING_REQ,
	PROTOCOL_SHOOTING_ACK,

	PROTOCOL_DAMAGE_REQ,
	PROTOCOL_DAMAGE_ACK,
};

struct POSITION {
	int mSessionNum;
	float mUserX;
	float mUserY;
	float mUserZ;
};

class PACKET_HEAD {
public:
	int mCmd;
	
};


//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : 유저 대미지  관련
//작성자 : 이원배
//일  시 : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_DAMAGE_REQ : public PACKET_HEAD {
public:
	PACKET_DAMAGE_REQ()
	{
		mCmd = PROTOCOL_DAMAGE_REQ;
	}
	int mRemainHp = 0;
};
class PACKET_DAMAGE_ACK : public PACKET_HEAD {
public:
	PACKET_DAMAGE_ACK()
	{
		mCmd = PROTOCOL_DAMAGE_ACK;
	}
	int mSessionNum = 0;
	int mRemainHp = 0;

};
//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : 유저 총알 발사 관련
//작성자 : 이원배
//일  시 : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_ATTACK_REQ : public PACKET_HEAD {
public:
	PACKET_ATTACK_REQ()
	{
		mCmd = PROTOCOL_SHOOTING_REQ;
	}
	 
};
class PACKET_ATTACK_ACK : public PACKET_HEAD {
public:
	PACKET_ATTACK_ACK()
	{
		mCmd = PROTOCOL_SHOOTING_ACK;
	}
	int mSessionNum = 0;
	 
};

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : 유저 회전 관련
//작성자 : 이원배
//일  시 : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_ROTATE_REQ : public PACKET_HEAD {
public:
	PACKET_ROTATE_REQ() 
	{
		mCmd = PROTOCOL_ROTATE_REQ;
	}
	float mRotate = 0.0f;
};
class PACKET_ROTATE_ACK : public PACKET_HEAD {
public:
	PACKET_ROTATE_ACK()
	{
		mCmd = PROTOCOL_ROTATE_ACK;
	}
	int mSessionNum = 0;
	float mRotate = 0.0f;
};


//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : 유저 리스트 관련
//작성자 : 이원배
//일  시 : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
class PACKET_START_REQ : public PACKET_HEAD {
public:
	PACKET_START_REQ()
	{
		mCmd = PROTOCOL_START_REQ;
	}
	POSITION mStartPosition;
};


class PACKET_MY_START_ACK : public PACKET_HEAD {
public:
	PACKET_MY_START_ACK()
	{
		mCmd = PROTOCOL_MY_START_ACK;
	}
	int mCount = 0;
	
	POSITION mUserPositionList[30];
};
class PACKET_ENEMY_START_ACK : public PACKET_HEAD {
public:
	PACKET_ENEMY_START_ACK()
	{
		mCmd = PROTOCOL_ENEMY_START_ACK;
	}
	 
	POSITION mAddUserPostion;
};

//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : 이동 패킷 관련
//작성자 : 이원배
//일  시 : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_MOVE_REQ : public PACKET_HEAD {
public:
	PACKET_MOVE_REQ() 
	{
		mCmd = PROTOCOL_MOVE_REQ;
	}
	POSITION mPositionInfo_req;
};
class PACKET_MOVE_ACK : public PACKET_HEAD {
public:
	PACKET_MOVE_ACK()
	{
		mCmd = PROTOCOL_MOVE_ACK;
	}
	POSITION mPositionInfo_ack;
};


//--------------------------------------------------------------------------------------------------------------------------------------
//목  적 : 유저 리스트 관련
//작성자 : 이원배
//일  시 : 2021. 04. 05
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------

class PACKET_ACCEPT_ACK : public PACKET_HEAD {
public:
	PACKET_ACCEPT_ACK()
	{
		mCmd = PROTOCOL_ACCEPT_ACK;
	}
	int mMySessionNum = 0;
	 
};
