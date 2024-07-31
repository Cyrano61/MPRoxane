// Copyright 2001 Chris Welty
//	All Rights Reserved

#ifndef ODK_ODKSTREAM_H
#define ODK_ODKSTREAM_H

#include "ggsstream.hpp"
#include "RXRoxane.hpp"

class RXRoxane;

class CODKStream: public ggsstream {
public:

	virtual void HandleGGS				(const CMsg* pmsg);
	virtual void HandleGGSLogin			();
	virtual void HandleGGSTell			(const CMsgGGSTell* pmsg);
	virtual void HandleGGSUnknown		(const CMsgGGSUnknown* pmsg);

	virtual void HandleOsJoin			(const CMsgOsJoin* pmsg);
	virtual void HandleOsLogin			();
	virtual void HandleOsUnknown		(const CMsgOsUnknown* pmsg);
	virtual void HandleOsUpdate			(const CMsgOsUpdate* pmsg);

	virtual void GetMoveIfNeeded(const string& idg);
	virtual void SendMove(const string& idg, COsMoveListItem& mli);
	virtual void SendMsg(const string& msg);

	virtual void HandleOsRequestDelta(const CMsgOsRequestDelta* pmsg);
	virtual void HandleOsGameOver(const CMsgOsMatchDelta* pmsg,const string& idg);

//	virtual void HandleOsMatchDelta(const CMsgOsMatchDelta* pmsg);
	
	RXRoxane* pComputer;
};

#endif // ODK_GGSSTREAM_H
