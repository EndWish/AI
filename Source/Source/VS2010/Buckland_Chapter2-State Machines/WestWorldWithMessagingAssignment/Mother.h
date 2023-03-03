#pragma once

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "MotherOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"

class Mother : public BaseGameEntity {
private:
	StateMachine<Mother>* m_pStateMachine;
	int sideDish;

public:
	Mother(int id);
	~Mother();

	StateMachine<Mother>* GetFSM() const;
	void AddSideDish(int value) { sideDish += value; };
	int GetSideDish() const { return sideDish; };

	void Update();
	virtual bool HandleMessage(const Telegram& msg);

};

