#include "Goal_Avoid.h"
#include "Goal_SeekToPosition.h"
#include "Goal_GetItem.h"
#include "../Raven_ObjectEnumerations.h"
#include "Goal_HuntTarget.h"
#include "Goal_DodgeSideToSide.h"
#include "../Raven_Bot.h"



#include <iostream>



//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_Avoid::Activate() {
    m_iStatus = active;

    //if this goal is reactivated then there may be some existing subgoals that
    //must be removed
    RemoveAllSubgoals();

    //it is possible for a bot's target to die whilst this goal is active so we
    //must test to make sure the bot always has an active target
    if (!m_pOwner->GetTargetSys()->isTargetPresent()) {
        m_iStatus = completed;
        return;
    }

    if (m_pOwner->GetTargetBot() && m_pOwner->Health() < m_pOwner->GetTargetBot()->Health()) {  // 상대방의 체력보다 낮을 경우
        std::cout << "내 체력 : " << m_pOwner->Health() << ", 상대 체력 : " << m_pOwner->GetTargetBot()->Health() << "\n";
        AddSubgoal(new Goal_GetItem(m_pOwner, type_health));    // 우선적으로 회복 아이템을 찾으러 간다.
    }
    else {
        AddSubgoal(new Goal_HuntTarget(m_pOwner));  // 적을 쫒는다.
    }
}

//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Goal_Avoid::Process() {
    //if status is inactive, call Activate()
    ActivateIfInactive();

    //process the subgoals
    m_iStatus = ProcessSubgoals();

    ReactivateIfFailed();

    return m_iStatus;
}




