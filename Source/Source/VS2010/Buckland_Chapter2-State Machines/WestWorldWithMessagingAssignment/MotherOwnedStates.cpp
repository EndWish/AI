#include "MotherOwnedStates.h"
#include "Mother.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

//-----------------------------------------------------------------------------
MotherGlobalState* MotherGlobalState::Instance() {
    static MotherGlobalState instance;

    return &instance;
}

void MotherGlobalState::Execute(Mother* mother) {
    //1 in 10 chance of needing the bathroom (provided she is not already
    //in the bathroom)
    if ((RandFloat() < 0.2) && !mother->GetFSM()->isInState(*VisitBathroom::Instance())) {
        mother->GetFSM()->ChangeState(VisitBathroom::Instance());
    }
}

bool MotherGlobalState::OnMessage(Mother* mother, const Telegram& msg) {

    return false;
}

//-----------------------------------------------------------------------------

HouseWork* HouseWork::Instance() {
    static HouseWork instance;

    return &instance;
}


void HouseWork::Enter(Mother* mother) {
    //cout << "\n" << GetNameOfEntity(mother->ID()) << ": �������� ������ ����.";
}

void HouseWork::Execute(Mother* mother) {
    switch (RandInt(0, 2)) {
    case 0:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": ��� ��� ���� ����..";
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": ���� �ִ� ����� �ɷ����� �ؾ߰ڳ�.";
        break;
    case 2:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": TV ���� ������ �о����.";
        break;
    }
    
    mother->AddSideDish(-1);

    if (mother->GetSideDish() <= 0) {
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": ������ �� �������� ���� ���߰ھ�.";
        mother->GetFSM()->ChangeState(Shopping::Instance());
    }

}

void HouseWork::Exit(Mother* mother) {
    
}

bool HouseWork::OnMessage(Mother* mother, const Telegram& msg) {
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg) {
    case Msg_HiHoneyImHome: {
        cout << GetNameOfEntity(mother->ID()) << "���� �� �޽����� ó���մϴ�. - " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

        mother->GetFSM()->ChangeState(Cook::Instance());

        cout << "\n" << GetNameOfEntity(mother->ID()) << ": �ڱⰡ �����ϱ� ����û� �غ� �غ���!";

        Dispatch->DispatchMessage(2, //time delay
            mother->ID(),        //ID of sender
            ent_Mother,            //ID of recipient
            Msg_DinnerIsReady,   //the message
            NO_ADDITIONAL_INFO);

        Dispatch->DispatchMessage(2, //time delay
            mother->ID(),        //ID of sender
            ent_Father,            //ID of recipient
            Msg_DinnerIsReady,   //the message
            NO_ADDITIONAL_INFO);
    }
    return true;

    }//end switch
    return false;
}

//-----------------------------------------------------------------------------

Shopping* Shopping::Instance() {
    static Shopping instance;

    return &instance;
}


void Shopping::Enter(Mother* mother) {
    
}


void Shopping::Execute(Mother* mother) {
    switch (RandInt(0, 2)) {
    case 0:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": ���� �� �ʿ�����";
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": ���, ���ڵ� ����������...";
        break;
    case 2:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": �Ŀ����� �����";
        break;
    }
    mother->AddSideDish(1);

    if (3 <= mother->GetSideDish()) {
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": �������� ����� ��� ����.";
        mother->GetFSM()->ChangeState(HouseWork::Instance());
    }
    
}

void Shopping::Exit(Mother* mother) {
    //cout << "\n" << GetNameOfEntity(mother->ID()) << ": �������� ����� ��� ����.";
}

bool Shopping::OnMessage(Mother* mother, const Telegram& msg) {
    return false;
}

//-----------------------------------------------------------------------------

Cook* Cook::Instance() {
    static Cook instance;
    return &instance;
}

void Cook::Enter(Mother* mother) {

}

void Cook::Execute(Mother* mother) {
    switch (RandInt(0, 2)) {
    case 0:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": ���ְ� ���� �ǰ��־�.";
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": ���� ������ ������ ���ְڴ°�.";
        break;
    case 2:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": �ع����鵵 �غ�����.";
        break;
    }

}

void Cook::Exit(Mother* mother) {
    
}

bool Cook::OnMessage(Mother* mother, const Telegram& msg) {
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg) {
    case Msg_DinnerIsReady: {
        cout << GetNameOfEntity(mother->ID()) << "���� �� �޽����� ó���մϴ�. - " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

        mother->GetFSM()->ChangeState(HouseWork::Instance());
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": ���� ���ְ� �Ƴ�.";
    }
    return true;

    }//end switch
    return false;

    return false;
}

//-----------------------------------------------------------------------------

VisitBathroom* VisitBathroom::Instance() {
    static VisitBathroom instance;

    return &instance;
}

void VisitBathroom::Enter(Mother* mother) {
    cout << "\n" << GetNameOfEntity(mother->ID()) << ": ���� ����..";
}

void VisitBathroom::Execute(Mother* mother) {

    cout << "\n" << GetNameOfEntity(mother->ID()) << ": ���ϵ� ����, ȭ�嵵 ��ġ��..";
    mother->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(Mother* mother) {
    
}

bool VisitBathroom::OnMessage(Mother* mother, const Telegram& msg) {
    return false;
}
