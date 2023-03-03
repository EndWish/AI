#include "Mother.h"

Mother::Mother(int id) : BaseGameEntity(id) {
	sideDish = 0;

	m_pStateMachine = new StateMachine<Mother>(this);

	m_pStateMachine->SetCurrentState(HouseWork::Instance());

	m_pStateMachine->SetGlobalState(MotherGlobalState::Instance());

}

Mother::~Mother() {
	delete m_pStateMachine;
}

StateMachine<Mother>* Mother::GetFSM() const {
	return m_pStateMachine;
}

void Mother::Update() {
	//set text color to blue
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	m_pStateMachine->Update();
}

bool Mother::HandleMessage(const Telegram& msg) {
	return m_pStateMachine->HandleMessage(msg);
}


