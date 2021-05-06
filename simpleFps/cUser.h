#pragma once
#include "Resource.h"
#include "cSession.h"
 
#include "cUserManager.h"

class cUser : public cSession
{
public:
	cUser();
	virtual ~cUser();

	void SetUserKey(int _userkey) { mUserKey = _userkey; }
	int GetUserKey()const { return mUserKey; }

	virtual void PacketParsing(PACKET_HEAD* _packet);
	typedef void (cUser::* pf)(PACKET_HEAD* _packet);

private:
	void START_FUNC(PACKET_HEAD* _packet);
	void MOVE_FUNC(PACKET_HEAD* _packet); 
	void ROTATE_FUNC(PACKET_HEAD* _packet);
	void SHOOTING_FUNC(PACKET_HEAD* _packet);
	void DAMAGE_FUNC(PACKET_HEAD* _packet);

	POSITION mUserPostion;

	map<int, pf> mMap;
	int mUserRemainHp; 
	int mUserKey;
};


