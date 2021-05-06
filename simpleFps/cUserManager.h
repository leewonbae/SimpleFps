#pragma once
#include "Resource.h"
#include "cUser.h"
#include "Packet.h"
#include "cSynchronization.h"

class cUserManager : public cSingleton<cUserManager>
{
	friend class cSingleton<cUserManager>;
public:

	 
	void InputStartPosition(POSITION* _position,cSession* _session);
	void UpdatePosition(cSession* _session, POSITION* _position);
	void RotateSendPacket(cSession* _session, float _rotate);
	void ShootingReq(cSession* _attack_session);
	void DamageReq(cSession* _damage_session,int _remainhp);

	

private:
	cUserManager();
	~cUserManager();

	 
 
	cCriticalSection mCS_UserMove_Lock;
	cCriticalSection mCS_UserDamage_Lock;
	 
	int mUserCount;
	vector<pair<cSession*,POSITION*>> mUserPositionList;
	 
};

