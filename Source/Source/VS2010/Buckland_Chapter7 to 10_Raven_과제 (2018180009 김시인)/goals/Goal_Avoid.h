#ifndef GOAL_AVOID_H
#define GOAL_AVOID_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Goal_Avoid.h
//
//  Author: Mat Buckland (ai-junkie.com)
//
//  Desc:   this goal makes the bot dodge from side to side
//
//-----------------------------------------------------------------------------
#include "Goals/Goal_Composite.h"
#include "Raven_Goal_Types.h"
#include "../Raven_Bot.h"





class Goal_Avoid : public Goal_Composite<Raven_Bot> {
public:

	Goal_Avoid(Raven_Bot* pOwner) :Goal_Composite<Raven_Bot>(pOwner, goal_avoid) {
	}

	void Activate();

	int  Process();

	void Terminate() { m_iStatus = completed; }

};






#endif
