#include "cUserManager.h"
cUserManager::cUserManager() :mUserCount(0)
{

}
cUserManager::~cUserManager()
{

}

void cUserManager::RotateSendPacket(cSession* _session, float _rotate)
{
	cSynchronization sync(mCS_UserMove_Lock);

	PACKET_ROTATE_ACK sendpacket;
	sendpacket.mSessionNum = _session->GetSessionNum();
	sendpacket.mRotate = _rotate;
	

	for (int i = 0;i < mUserPositionList.size();i++)
	{
		if (mUserPositionList[i].first == _session)
		{

			continue;
		}
		else
		{
			mUserPositionList[i].first->OnSend(&sendpacket, sizeof(PACKET_ROTATE_ACK));
		}
	}

}
void cUserManager::UpdatePosition(cSession* _session, POSITION* _position)
{
	cSynchronization sync(mCS_UserMove_Lock);

	PACKET_MOVE_ACK sendpacket;
	memcpy(&sendpacket.mPositionInfo_ack, _position, sizeof(POSITION));


	for (int i = 0;i < mUserPositionList.size();i++)
	{
		if (mUserPositionList[i].first == _session)
		{
			 
			continue;
		}
		else
		{
			mUserPositionList[i].first->OnSend(&sendpacket, sizeof(PACKET_MOVE_ACK));
		}
	}

}
void cUserManager::InputStartPosition(POSITION* _position, cSession* _session)
{
	cSynchronization sync(mCS_UserMove_Lock);
	PACKET_MY_START_ACK my_sendpacket;
	PACKET_ENEMY_START_ACK enemy_sendpacket;

	mUserPositionList.push_back(make_pair(_session, _position));
	int count = 0;
	mUserCount++;
	 
	
	memcpy(&enemy_sendpacket.mAddUserPostion, _position, sizeof(POSITION));


	if (mUserPositionList.size() >= 2)
	{
		for (int i = 0;i < mUserPositionList.size();i++)
		{

			if (mUserPositionList[i].first == _session)
			{

				continue;
			}
			else
			{
				mUserPositionList[i].first->OnSend(&enemy_sendpacket,
					sizeof(PACKET_ENEMY_START_ACK));

				memcpy(&my_sendpacket.mUserPositionList[count],
					mUserPositionList[i].second, sizeof(POSITION));
				count++;
			}
		}
		
		my_sendpacket.mCount = count;
		_session->OnSend(&my_sendpacket, sizeof(PACKET_MY_START_ACK));
	}
	


}

void cUserManager::ShootingReq(cSession* _attack_session)
{
	
	cSynchronization sync(mCS_UserDamage_Lock);
	PACKET_ATTACK_ACK sendpacket;
	sendpacket.mSessionNum = _attack_session->GetSessionNum();

	for (int i = 0;i < mUserPositionList.size();i++)
	{
		if (mUserPositionList[i].first == _attack_session)
		{
			continue;
		}
		else
		{
			mUserPositionList[i].first->OnSend(&sendpacket, sizeof(PACKET_ATTACK_ACK));
		}
	}
	



}
void cUserManager::DamageReq(cSession* _attack_session, int _remainhp)
{

	cSynchronization sync(mCS_UserDamage_Lock);
	PACKET_DAMAGE_ACK sendpacket;
	sendpacket.mSessionNum = _attack_session->GetSessionNum();
	sendpacket.mRemainHp = _remainhp;
	int index = 0;
	for (int i = 0;i < mUserPositionList.size();i++)
	{
		if (mUserPositionList[i].first == _attack_session)
		{
			index = i;
			continue;
		}
		else
		{
			mUserPositionList[i].first->OnSend(&sendpacket, sizeof(PACKET_DAMAGE_ACK));
		}
	}

	cSynchronization sync2(mCS_UserMove_Lock);

	if (_remainhp == 0)
	{
		
		mUserPositionList.erase(mUserPositionList.begin()+index);
	}

}

 