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
        cout << GetNameOfEntity(child->ID()) << "���� �� �޽����� ó���մϴ�. - " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(child->ID()) << ": �ƹ��� ������";
        child->AddMoney(1); // 1�޷��� ��´�.

        if (enoughMoney <= child->GetMoney()) { // ���� ����� ���ϰ��
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
    cout << "\n" << GetNameOfEntity(child->ID()) << ": �Ƿΰ� �׿��� �������� �ھ�.";
}


void SleepOrRest::Execute(Child* child) {
    switch (RandInt(0, 1)) {
    case 0:
        cout << "\n" << GetNameOfEntity(child->ID()) << ": ZZZ...(�����̳� +4)";
        child->AddStamina(4);
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(child->ID()) << ": �߱��豼 (�����̳� +2)";
        child->AddStamina(2);
        break;
    }

    if (maxStamina <= child->GetStamina()) {
        child->GetFSM()->ChangeState(Study::Instance());
    }

}

void SleepOrRest::Exit(Child* child) {
    cout << "\n" << GetNameOfEntity(child->ID()) << ": ����� ������. (���׹̳� "<< child->GetStamina() <<")";
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
    cout << "\n" << GetNameOfEntity(child->ID()) << ": ���θ� ������ ����!";
}


void Study::Execute(Child* child) {

    switch (RandInt(0, 1)) {
    case 0:
        cout << "\n" << GetNameOfEntity(child->ID()) << ": ��� �ڿ����� ���� -1/12 ��";
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(child->ID()) << ": ��������(ˣ����ܨ)�� 1884�� 12�� 4�Ͽ� �Ͼ��.";
        break;
    }
    child->AddStamina(-RandInt(1,2));

    if (child->GetStamina() <= 0) {
        child->GetFSM()->ChangeState(SleepOrRest::Instance());
    }

}

void Study::Exit(Child* child) {
    cout << "\n" << GetNameOfEntity(child->ID()) << ": ���� ���δ� �����...";
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
    cout << "\n" << GetNameOfEntity(child->ID()) << ": ������ ���� ������ �غ���";
}

void PlayInThePCRoom::Execute(Child* child) {

    switch (RandInt(0, 1)) {
    case 0:
        cout << "\n" << GetNameOfEntity(child->ID()) << ": �ְ��� �÷��� - Child";
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(child->ID()) << ": ������ �� ���̾Ʒ� �±��ϰ� ������";
        break;
    }
    child->AddMoney(-1);

    if (child->GetMoney() <= 0) {
        child->GetFSM()->RevertToPreviousState();
    }

}

void PlayInThePCRoom::Exit(Child* child) {
    cout << "\n" << GetNameOfEntity(child->ID()) << ": ��հ� ��Ҵ�. ";
    if (child->GetFSM()->PreviousState() == Study::Instance()) {
        cout << "�ٽ� ���θ� �Ϸ� ���� �ھ�.";
    }
    else if (child->GetFSM()->PreviousState() == SleepOrRest::Instance()) {
        cout << "���� ���� ������";
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
    cout << "\n" << GetNameOfEntity(child->ID()) << ": ���� �Ӹ��� �������� �߰ſ�.";
}

void Sick::Execute(Child* child) {

    cout << "\n" << GetNameOfEntity(child->ID()) << ": ���ݾ� ������ ���� �����̾�.";

    child->AddHealth(1);

    if (normalHealth <= child->GetHealth()) {
        child->GetFSM()-> RevertToPreviousState();
    }
}

void Sick::Exit(Child* child) {
    cout << "\n" << GetNameOfEntity(child->ID()) << ": ��Ȱ!";
}

bool Sick::OnMessage(Child* child, const Telegram& msg) {
    return false;
}
