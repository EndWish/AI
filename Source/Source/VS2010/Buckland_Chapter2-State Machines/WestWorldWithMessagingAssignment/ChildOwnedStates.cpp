#include "ChildOwnedStates.h"
#include "Child.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

//-----------------------------------------------------------------------------
ChildGlobalState* ChildGlobalState::Instance() {
    static ChildGlobalState instance;

    return &instance;
}

void ChildGlobalState::Execute(Child* child) {
    //1 in 10 chance of needing the bathroom (provided she is not already
    //in the bathroom)
    if ((RandFloat() < 0.1) && !child->GetFSM()->isInState(*Sick::Instance())) {
        child->GetFSM()->ChangeState(Sick::Instance());
        child->SetHealth(RandInt(0, 3));
    }
}

bool ChildGlobalState::OnMessage(Child* child, const Telegram& msg) {
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg) {
    case Msg_SonTakeYourPocketMoney: {
        cout << GetNameOfEntity(child->ID()) << "에게 온 메시지를 처리합니다. - " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(child->ID()) << ": 아버지 용돈 고마워요";
        child->AddMoney(1); // 1달러를 얻는다.

        if (enoughMoney <= child->GetMoney() && child->GetFSM()->CurrentState() != Sick::Instance()) { // 돈이 충분히 모일경우
            cout << "\n" << GetNameOfEntity(child->ID()) << ": 돈이 충분히 보였으니 PC 가야지";
            child->GetFSM()->ChangeState(PlayInThePCRoom::Instance());
        }
    }
    return true;

    }//end switch

    return false;
}

//-----------------------------------------------------------------------------

SleepOrRest* SleepOrRest::Instance() {
    static SleepOrRest instance;

    return &instance;
}


void SleepOrRest::Enter(Child* child) {
    
}


void SleepOrRest::Execute(Child* child) {
    switch (RandInt(0, 1)) {
    case 0:
        cout << "\n" << GetNameOfEntity(child->ID()) << ": ZZZ...(스테이나 +4)";
        child->AddStamina(4);
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(child->ID()) << ": 뒹굴됭굴 (스테이나 +2)";
        child->AddStamina(2);
        break;
    }

    if (maxStamina <= child->GetStamina()) {
        cout << "\n" << GetNameOfEntity(child->ID()) << ": 충분히 쉬었어. 다시 공부하자! (스테미나 " << child->GetStamina() << ")";
        child->GetFSM()->ChangeState(Study::Instance());
    }

}

void SleepOrRest::Exit(Child* child) {
    
}

bool SleepOrRest::OnMessage(Child* child, const Telegram& msg) {
    return false;
}

//-----------------------------------------------------------------------------

Study* Study::Instance() {
    static Study instance;

    return &instance;
}


void Study::Enter(Child* child) {
    
}


void Study::Execute(Child* child) {

    switch (RandInt(0, 1)) {
    case 0:
        cout << "\n" << GetNameOfEntity(child->ID()) << ": 모든 자연수의 합은 -1/12 야";
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(child->ID()) << ": 갑신정변(甲申政變)은 1884년 12월 4일에 일어났어.";
        break;
    }
    child->AddStamina(-RandInt(1,2));

    if (child->GetStamina() <= 0) {
        cout << "\n" << GetNameOfEntity(child->ID()) << ": 피로가 쌓여서 쉬러가야 겠어.";
        child->GetFSM()->ChangeState(SleepOrRest::Instance());
    }

}

void Study::Exit(Child* child) {
    //cout << "\n" << GetNameOfEntity(child->ID()) << ": 역시 공부는 힘들어...";
}

bool Study::OnMessage(Child* child, const Telegram& msg) {
    return false;
}

//-----------------------------------------------------------------------------

PlayInThePCRoom* PlayInThePCRoom::Instance() {
    static PlayInThePCRoom instance;

    return &instance;
}

void PlayInThePCRoom::Enter(Child* child) {
    
}

void PlayInThePCRoom::Execute(Child* child) {

    switch (RandInt(0, 1)) {
    case 0:
        cout << "\n" << GetNameOfEntity(child->ID()) << ": 최고의 플레이 - Child";
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(child->ID()) << ": 오늘은 꼭 다이아로 승급하고 말꺼야";
        break;
    }
    child->AddMoney(-1);

    if (child->GetMoney() <= 0) {
        cout << "\n" << GetNameOfEntity(child->ID()) << ": 돈이 다떨어 졌네 아쉽다.";
        if (child->GetFSM()->PreviousState() == Study::Instance()) {
            cout << "다시 공부를 하러 가야 겠어.";
        }
        else if (child->GetFSM()->PreviousState() == SleepOrRest::Instance()) {
            cout << "이제 집에 가야지";
        }

        child->GetFSM()->RevertToPreviousState();
    }

}

void PlayInThePCRoom::Exit(Child* child) {

}

bool PlayInThePCRoom::OnMessage(Child* child, const Telegram& msg) {
    return false;
}

//-----------------------------------------------------------------------------

Sick* Sick::Instance() {
    static Sick instance;

    return &instance;
}

void Sick::Enter(Child* child) {
    cout << "\n" << GetNameOfEntity(child->ID()) << ": 갑자기 몸상태가 안좋아졌어...";
}

void Sick::Execute(Child* child) {

    cout << "\n" << GetNameOfEntity(child->ID()) << ": 으으 머리가 어지럽고 뜨거워.";

    child->AddHealth(1);

    if (normalHealth <= child->GetHealth()) {
        cout << "\n" << GetNameOfEntity(child->ID()) << ": 드디어 몸이 다 낫았어. 다시 원래하던걸 해야겠어.";
        child->GetFSM()-> RevertToPreviousState();
    }
}

void Sick::Exit(Child* child) {
    //cout << "\n" << GetNameOfEntity(child->ID()) << ": 부활!";
}

bool Sick::OnMessage(Child* child, const Telegram& msg) {
    return false;
}
