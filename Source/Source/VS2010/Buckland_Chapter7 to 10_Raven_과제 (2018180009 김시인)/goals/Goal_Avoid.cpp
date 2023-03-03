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

    if (m_pOwner->GetTargetBot() && m_pOwner->Health() < m_pOwner->GetTargetBot()->Health()) {  // ������ ü�º��� ���� ���
        std::cout << "�� ü�� : " << m_pOwner->Health() << ", ��� ü�� : " << m_pOwner->GetTargetBot()->Health() << "\n";
        AddSubgoal(new Goal_GetItem(m_pOwner, type_health));    // �켱������ ȸ�� �������� ã���� ����.
    }
    else {
        AddSubgoal(new Goal_HuntTarget(m_pOwner));  // ���� �i�´�.
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




