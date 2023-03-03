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
    //cout << "\n" << GetNameOfEntity(mother->ID()) << ": 집안일을 시작해 볼까.";
}

void HouseWork::Execute(Mother* mother) {
    switch (RandInt(0, 2)) {
    case 0:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": 쓸어도 쓸어도 끝이 없네..";
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": 여기 있는 얼룩은 걸래질을 해야겠네.";
        break;
    case 2:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": TV 위에 먼지도 털어야지.";
        break;
    }
    
    mother->AddSideDish(-1);

    if (mother->GetSideDish() <= 0) {
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": 반찬이 다 떨어져서 장을 봐야겠어.";
        mother->GetFSM()->ChangeState(Shopping::Instance());
    }

}

void HouseWork::Exit(Mother* mother) {
    
}

bool HouseWork::OnMessage(Mother* mother, const Telegram& msg) {
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg) {
    case Msg_HiHoneyImHome: {
        cout << GetNameOfEntity(mother->ID()) << "에게 온 메시지를 처리합니다. - " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

        mother->GetFSM()->ChangeState(Cook::Instance());

        cout << "\n" << GetNameOfEntity(mother->ID()) << ": 자기가 왔으니까 저녁시사 준비를 해볼까!";

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
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": 쌀은 꼭 필요하지";
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": 당근, 감자도 떨어졌었지...";
        break;
    case 2:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": 식용유도 사야해";
        break;
    }
    mother->AddSideDish(1);

    if (3 <= mother->GetSideDish()) {
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": 이정도면 충분히 산거 같아.";
        mother->GetFSM()->ChangeState(HouseWork::Instance());
    }
    
}

void Shopping::Exit(Mother* mother) {
    //cout << "\n" << GetNameOfEntity(mother->ID()) << ": 이정도면 충분히 산거 같아.";
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
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": 맛있게 밥이 되고있어.";
        break;
    case 1:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": 국도 끓여서 먹으면 맛있겠는걸.";
        break;
    case 2:
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": 밑반찬들도 준비하자.";
        break;
    }

}

void Cook::Exit(Mother* mother) {
    
}

bool Cook::OnMessage(Mother* mother, const Telegram& msg) {
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg) {
    case Msg_DinnerIsReady: {
        cout << GetNameOfEntity(mother->ID()) << "에게 온 메시지를 처리합니다. - " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

        mother->GetFSM()->ChangeState(HouseWork::Instance());
        cout << "\n" << GetNameOfEntity(mother->ID()) << ": 밥이 맛있게 됐네.";
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
    cout << "\n" << GetNameOfEntity(mother->ID()) << ": 급한 볼일..";
}

void VisitBathroom::Execute(Mother* mother) {

    cout << "\n" << GetNameOfEntity(mother->ID()) << ": 볼일도 보고, 화장도 고치고..";
    mother->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(Mother* mother) {
    
}

bool VisitBathroom::OnMessage(Mother* mother, const Telegram& msg) {
    return false;
}
