#include "FatherOwnedStates.h"
#include "Father.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

//-----------------------------------------------------------------------------
FatherGlobalState* FatherGlobalState::Instance() {
    static FatherGlobalState instance;

    return &instance;
}

void FatherGlobalState::Execute(Father* father) {
    //1 in 10 chance of needing the bathroom (provided she is not already
    //in the bathroom)
    if ((RandFloat() < 0.1) && !father->GetFSM()->isInState(*BusinessTrip::Instance())) {
        father->GetFSM()->ChangeState(BusinessTrip::Instance());
        father->SetBusinessTripGauge(RandInt(3, 5));
    }
}

bool FatherGlobalState::OnMessage(Father* father, const Telegram& msg) {

    return false;
}

//-----------------------------------------------------------------------------

GoHomeAndSsleep* GoHomeAndSsleep::Instance() {
    static GoHomeAndSsleep instance;

    return &instance;
}


void GoHomeAndSsleep::Enter(Father* father) {
    //cout << "\n" << GetNameOfEntity(father->ID()) << ": ����߰ھ�.";
}

void GoHomeAndSsleep::Execute(Father* father) {
    cout << "\n" << GetNameOfEntity(father->ID()) << ": ZZZ...";
    father->AddMoney(-1);

    if (father->GetMoney() <= 0) {
        cout << "\n" << GetNameOfEntity(father->ID()) << ": �ٽ� ���� ���� ��� �غ���.";
        father->GetFSM()->ChangeState(WorkForACompany::Instance());
    }

}

void GoHomeAndSsleep::Exit(Father* father) {
    //cout << "\n" << GetNameOfEntity(father->ID()) << ": ����� ������.";
}

bool GoHomeAndSsleep::OnMessage(Father* father, const Telegram& msg) {
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg) {
    case Msg_DinnerIsReady: {
        cout << GetNameOfEntity(father->ID()) << "���� �� �޽����� ó���մϴ�. - " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        father->GetFSM()->ChangeState(Eat::Instance());
    }
    return true;

    }//end switch
    return false;
}

//-----------------------------------------------------------------------------

Eat* Eat::Instance() {
    static Eat instance;

    return &instance;
}


void Eat::Enter(Father* father) {
    
}


void Eat::Execute(Father* father) {
    cout << "\n" << GetNameOfEntity(father->ID()) << ": ���� ���ִ� ��!";
    cout << "\n" << GetNameOfEntity(father->ID()) << ": ��θ��� �� �Ծ���.";
    father->GetFSM()->ChangeState(GoHomeAndSsleep::Instance());
}

void Eat::Exit(Father* father) {
    
}

bool Eat::OnMessage(Father* father, const Telegram& msg) {
    return false;
}

//-----------------------------------------------------------------------------

WorkForACompany* WorkForACompany::Instance() {
    static WorkForACompany instance;

    return &instance;
}

void WorkForACompany::Enter(Father* father) {
    
}

void WorkForACompany::Execute(Father* father) {
    switch (RandInt(0, 2)) {
    case 0:
        cout << "\n" << GetNameOfEntity(father->ID()) << ": ������ ��� �ľ��ؾ߰ڱ�.";
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(father->ID()) << ": ���� ȿ������ ȫ������� �м��ؾ߰ھ�.";
        break;
    case 2:
        cout << "\n" << GetNameOfEntity(father->ID()) << ": �� ���� ȸ�ǿ� ���� �ڷ���� �غ��ؾ߰ڴ°�.";
        break;
    }

    father->AddMoney(RandInt(1, 3));
    if (RandInt(0,1) == 0) {    // 1/2Ȯ���� �Ƶ鿡�� �뵷�� �ش�.
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            father->ID(),        //ID of sender
            ent_Child,            //ID of recipient
            Msg_SonTakeYourPocketMoney,   //the message
            NO_ADDITIONAL_INFO);
    }

    if (5 <= father->GetMoney() ) {
        father->GetFSM()->ChangeState(GoHomeAndSsleep::Instance());
        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "\n" << GetNameOfEntity(father->ID()) << ": ���� ����̴�. ";
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            father->ID(),        //ID of sender
            ent_Mother,            //ID of recipient
            Msg_HiHoneyImHome,   //the message
            NO_ADDITIONAL_INFO);
    }

}

void WorkForACompany::Exit(Father* father) {
    
}

bool WorkForACompany::OnMessage(Father* father, const Telegram& msg) {
    return false;
}

//-----------------------------------------------------------------------------

BusinessTrip* BusinessTrip::Instance() {
    static BusinessTrip instance;

    return &instance;
}

void BusinessTrip::Enter(Father* father) {
    cout << "\n" << GetNameOfEntity(father->ID()) << ": �̹� ���嵵 ����� �̰ڱ�.";
}

void BusinessTrip::Execute(Father* father) {

    cout << "\n" << GetNameOfEntity(father->ID()) << ": ������ ó���ϰ� ���ư���.";
    father->GetFSM()->RevertToPreviousState();
}

void BusinessTrip::Exit(Father* father) {
    cout << "\n" << GetNameOfEntity(father->ID()) << ": �̹� ���嵵 �� ������ �Ʊ�.";
}

bool BusinessTrip::OnMessage(Father* father, const Telegram& msg) {
    return false;
}
