#include "Child.h"

Child::Child(int id) : BaseGameEntity(id) {
	stamina = maxStamina;
	health = normalHealth;
	money = 0;

	m_pStateMachine = new StateMachine<Child>(this);

	m_pStateMachine->SetCurrentState(SleepOrRest::Instance());

	m_pStateMachine->SetGlobalState(ChildGlobalState::Instance());

}

Child::~Child() {
	delete m_pStateMachine;
}

StateMachine<Child>* Child:: GetFSM() const { 
	return m_pStateMachine; 
}

void Child::Update() {
	//set text color to blue
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	m_pStateMachine->Update();
}

bool Child::HandleMessage(const Telegram& msg) {
	return m_pStateMachine->HandleMessage(msg);
}


