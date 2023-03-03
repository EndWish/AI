#pragma once

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "FatherOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"

class Father : public BaseGameEntity {
private:
	StateMachine<Father>* m_pStateMachine;
	int money; 
	int businessTripGauge;

public:
	Father(int id);
	~Father();

	StateMachine<Father>* GetFSM() const;
	void SetBusinessTripGauge(int value) { businessTripGauge = value; };
	void AddBusinessTripGauge(int value) { businessTripGauge += value; };
	int GetBusinessTripGauge() const { return businessTripGauge; };
	void AddMoney(int value) { money += value; };
	int GetMoney() const { return money; };

	void Update();
	virtual bool HandleMessage(const Telegram& msg);

};

