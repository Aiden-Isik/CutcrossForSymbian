// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include "ConditionActionController.h"
#include "TimeController.h"
#include "ActionController.h"

#define KTIME_FIELD_IGNORE -1

CConditionActionController *CConditionActionController::iInstance = NULL;

// Run the main condition-action loop
void CConditionActionController::RunLoopL()
{
    // Condition and action controllers
    CTimeController *timeController = CTimeController::GetInstanceL();
    CActionController *actionController = CActionController::GetInstanceL();

    // Loop forever until something deliberately breaks out of the loop
    while(true)
    {
        // Update all conditions
        timeController->UpdateTime();

        // We have a member struct called iConditions which contains information about every
        // set of conditions set up by the user. For every set, check if the condition has been met,
        // and if it has, fire the associated actions.
        for(TUint16 i = 0; i < iConditions.count; i++)
        {
            // Retrieve current conditions and compare them against the conditions to fire actions on.
            TUint16 totalConditions = 0;
            TUint16 metConditions = 0;

            // Time condition present
            if(iConditions.conditions[i].timeCondition)
            {
                totalConditions++;

                TDateTime *targetDateTime = &(iConditions.conditions[i].timeCondition->time);
                TDateTime currentDateTime = timeController->GetTime();

                // Check that the time specified by the user is the current time.
                // KTIME_FIELD_IGNORE is used to ignore e.g. the year, if the user wishes to fire
                // actions every year for a certain month/day/hour/minute.
                if((currentDateTime.Year() == targetDateTime->Year() || targetDateTime->Year() == KTIME_FIELD_IGNORE)
                   && (currentDateTime.Month() == targetDateTime->Month() || targetDateTime->Month() == KTIME_FIELD_IGNORE)
                   && (currentDateTime.Day() == targetDateTime->Month() || targetDateTime->Month() == KTIME_FIELD_IGNORE)
                   && (currentDateTime.Hour() == targetDateTime->Hour() || targetDateTime->Hour() == KTIME_FIELD_IGNORE)
                   && (currentDateTime.Minute() == targetDateTime->Minute() || targetDateTime->Minute() == KTIME_FIELD_IGNORE))
                {
                    // If this time condition has not yet fired actions, count as a valid condition.
                    // Also set hasFired to prevent duplicate firings.
                    if(!iConditions.conditions[i].hasFired)
                    {
                        iConditions.conditions[i].hasFired = true;
                        metConditions++;
                    }
                }
                else
                {
                    // The time condition has not been met. Fire next time it is.
                    iConditions.conditions[i].hasFired = false;
                }
            }

            // If the met conditions equals the total number of conditions, every required condition
            // was satisfied. Fire the appropriate actions.
            if(totalConditions == metConditions)
            {
                // Fire the vibration action, if it exists
                if(iConditions.conditions[i].vibrationAction)
                {
                    TUint16 duration = iConditions.conditions[i].vibrationAction->duration;
                    TInt8 intensity = iConditions.conditions[i].vibrationAction->intensity;
                    actionController->VibrateL(duration, intensity);
                }
            }
        }
    }
}

CConditionActionController::CConditionActionController()
{
}

// Stand-in constructor
// This should be called in place of the standard constructor, to enforce
// only one object for this class (singleton)
CConditionActionController *CConditionActionController::GetInstanceL()
{
    if(iInstance == NULL)
    {
        // NOTE: there is no need to deal with the cleanup stack here,
        // as this is a static method.
        iInstance = new(ELeave) CConditionActionController();
    }
    
    return iInstance;
}
