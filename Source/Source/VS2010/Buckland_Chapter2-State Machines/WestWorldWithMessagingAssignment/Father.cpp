#include "Father.h"

Father::Father(int id) : BaseGameEntity(id) {
	money = 0;
	businessTripGauge = 0;

	m_pStateMachine = new StateMachine<Father>(this);

	m_pStateMachine->SetCurrentState(GoHomeAndSsleep::Instance());

	m_pStateMachine->SetGlobalState(FatherGlobalState::Instance());

}

Father::~Father() {
	delete m_pStateMachine;
}

StateMachine<Father>* Father::GetFSM() const {
	return m_pStateMachine;
}

void Father::Update() {
	//set text color to blue
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	m_pStateMachine->Update();
}

bool Father::HandleMessage(const Telegram& msg) {
	return m_pStateMachine->HandleMessage(msg);
}


