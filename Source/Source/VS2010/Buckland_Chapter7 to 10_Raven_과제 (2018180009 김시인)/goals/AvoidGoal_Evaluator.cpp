#include "AvoidGoal_Evaluator.h"
#include "../navigation/Raven_PathPlanner.h"
#include "../Raven_ObjectEnumerations.h"
#include "../lua/Raven_Scriptor.h"
#include "misc/Stream_Utility_Functions.h"
#include "Raven_Feature.h"

#include "Goal_Think.h"
#include "Raven_Goal_Types.h"




//---------------- CalculateDesirability -------------------------------------
//-----------------------------------------------------------------------------
double AvoidGoal_Evaluator::CalculateDesirability(Raven_Bot* pBot)
{
    double Desirability = 0.0;

    //only do the calculation if there is a target present
    if (pBot->GetTargetSys()->isTargetPresent()) {
        const double Tweaker = 1.0;
        
        Desirability = Tweaker * (1 - Raven_Feature::Health(pBot)) * (1 - Raven_Feature::DistanceToItem(pBot, type_health) );
        Raven_Bot* targetBot = pBot->GetTargetBot();
        if (targetBot)
            Desirability *= 2 - Raven_Feature::Score(targetBot);

        //bias the value according to the personality of the bot
        Desirability *= m_dCharacterBias;
    }

  return Desirability;
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void AvoidGoal_Evaluator::SetGoal(Raven_Bot* pBot)
{
  pBot->GetBrain()->AddGoal_Avoid();
  
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void AvoidGoal_Evaluator::RenderInfo(Vector2D Position, Raven_Bot* pBot)
{
  //gdi->TextAtPos(Position, "EX: " + ttos(CalculateDesirability(pBot), 2));
}