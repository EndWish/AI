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
    if ((RandFloat() < 0.1) &&
        !child->GetFSM()->isInState(*Sick::Instance())) {
        child->GetFSM()->ChangeState(Sick::Instance());
        child->SetHealth(RandInt(0, 3));
    }
}

bool ChildGlobalState::OnMessage(Child* child, const Telegram& msg) {
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg) {
    case Msg_SonTakeYourPocketMoney: {
        cout << GetNameOfEntity(child->ID()) << "에게 온 메시지를 처리합니다. - " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(child->ID()) << ": 아버지 고마워요";
        child->AddMoney(1); // 1달러를 얻는다.

        if (enoughMoney <= child->GetMoney()) { // 돈이 충분히 모일경우
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
    cout << "\n" << GetNameOfEntity(child->ID()) << ": 피로가 쌓여서 쉬러가야 겠어.";
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
        child->GetFSM()->ChangeState(Study::Instance());
    }

}

void SleepOrRest::Exit(Child* child) {
    cout << "\n" << GetNameOfEntity(child->ID()) << ": 충분히 쉬었어. (스테미나 "<< child->GetStamina() <<")";
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
    cout << "\n" << GetNameOfEntity(child->ID()) << ": 공부를 시작해 볼까!";
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
        child->GetFSM()->ChangeState(SleepOrRest::Instance());
    }

}

void Study::Exit(Child* child) {
    cout << "\n" << GetNameOfEntity(child->ID()) << ": 역시 공부는 힘들어...";
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
    cout << "\n" << GetNameOfEntity(child->ID()) << ": 오늘은 무슨 게임을 해볼까";
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
        child->GetFSM()->RevertToPreviousState();
    }

}

void PlayInThePCRoom::Exit(Child* child) {
    cout << "\n" << GetNameOfEntity(child->ID()) << ": 재밌게 놀았다. ";
    if (child->GetFSM()->PreviousState() == Study::Instance()) {
        cout << "다시 공부를 하러 가야 겠어.";
    }
    else if (child->GetFSM()->PreviousState() == SleepOrRest::Instance()) {
        cout << "이제 집에 가야지";
    }
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
    cout << "\n" << GetNameOfEntity(child->ID()) << ": 으으 머리가 어지럽고 뜨거워.";
}

void Sick::Execute(Child* child) {

    cout << "\n" << GetNameOfEntity(child->ID()) << ": 조금씩 괜찮아 지는 느낌이야.";

    child->AddHealth(1);

    if (normalHealth <= child->GetHealth()) {
        child->GetFSM()-> RevertToPreviousState();
    }
}

void Sick::Exit(Child* child) {
    cout << "\n" << GetNameOfEntity(child->ID()) << ": 부활!";
}

bool Sick::OnMessage(Child* child, const Telegram& msg) {
    return false;
}
