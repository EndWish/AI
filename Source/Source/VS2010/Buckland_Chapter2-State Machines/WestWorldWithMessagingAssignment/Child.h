#pragma once

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "ChildOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"

const int maxStamina = 10;
const int normalHealth = 5;
const int enoughMoney = 3;

class Child : public BaseGameEntity {
private:
	StateMachine<Child>* m_pStateMachine;
	int stamina;
	int health;
	int money;

public:
	Child(int id);
	~Child();

	StateMachine<Child>* GetFSM() const;
	void SetHealth(int value) { health = value; };
	void AddHealth(int value) { health += value; };
	int GetHealth() const { return health; };
	void AddMoney(int value) { money += value; };
	int GetMoney() const { return money; };
	void AddStamina(int value) { stamina += value; };
	int GetStamina() const { return stamina; };

	void Update();
	virtual bool HandleMessage(const Telegram& msg);
	


};

