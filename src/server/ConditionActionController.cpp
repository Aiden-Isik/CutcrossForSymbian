// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include "ConditionActionController.h"
#include "ConditionActionData.h"
#include "TimeController.h"
#include "ActionController.h"
#include "FileHandler.h"
#include "Bit.h"

CConditionActionController *CConditionActionController::iInstance = NULL;

// Clear the condition-action entries
void CConditionActionController::CleanupConditionActions()
{
    // Free up any memory currently taken by the condition-action entries.
    // Also set any remaining fields to their default values.
    if(iConditions.conditions)
    {
        if(iConditions.conditions->timeCondition)
        {
            delete iConditions.conditions->timeCondition;
        }

        if(iConditions.conditions->vibrationAction)
        {
            delete iConditions.conditions->vibrationAction;
        }

        delete iConditions.conditions;
    }

    iConditions.count = 0;
    return;
}

// Initialise the condition-action controller
void CConditionActionController::InitialiseL()
{
    // Load file if it exists. If it does not, trap the leave
    // and ignore it, it might just have not been created yet.
    CFileHandler *fileHandler = CFileHandler::GetInstanceL();
    struct Conditions loadResult;
    TRAPD(error, loadResult=fileHandler->LoadConditionDataL(KSAVE_FILE_PATH));

    if(error == KErrNone)
    {
        // File loaded successfully, clean up the current condition-actions and store its data
        CleanupConditionActions();
        iConditions = loadResult;
    }
    else if(error != KErrPathNotFound)
    {
        // Re-leave with the same error we received
        User::Leave(error);
    }

    return;
}

// Run the main condition-action loop
void CConditionActionController::RunLoopL()
{
    // Condition and action controllers
    CTimeController *timeController = CTimeController::GetInstanceL();
    CActionController *actionController = CActionController::GetInstanceL();

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
            TUint8 usedTimes = iConditions.conditions[i].timeCondition->used;

            // Check that the time specified by the user is the current time.
            if((currentDateTime.Year() == targetDateTime->Year() || !BITFIELD_BIT(usedTimes, KTIME_USED_YEAR_BIT))
               && (currentDateTime.Month() == targetDateTime->Month() || !BITFIELD_BIT(usedTimes, KTIME_USED_MONTH_BIT))
               && (currentDateTime.Day() == targetDateTime->Day() || !BITFIELD_BIT(usedTimes, KTIME_USED_DAY_BIT))
               && (currentDateTime.Hour() == targetDateTime->Hour() || !BITFIELD_BIT(usedTimes, KTIME_USED_HOUR_BIT))
               && (currentDateTime.Minute() == targetDateTime->Minute() || !BITFIELD_BIT(usedTimes, KTIME_USED_MINUTE_BIT)))
            {
                metConditions++;
            }
        }

        // If the met conditions equals the total number of conditions, every required condition
        // was satisfied. Fire the appropriate actions.
        if(totalConditions == metConditions)
        {
            // If we have already fired actions for these conditions, don't do it again.
            // This prevents duplicate firing on every condition-action loop.
            if(!iConditions.conditions[i].hasFired)
            {
                iConditions.conditions[i].hasFired = true;

                // Fire the vibration action, if it exists
                if(iConditions.conditions[i].vibrationAction)
                {
                    TUint16 duration = iConditions.conditions[i].vibrationAction->duration;
                    TInt8 intensity = iConditions.conditions[i].vibrationAction->intensity;
                    actionController->VibrateL(duration, intensity);
                }
            }
        }
        else // If totalConditions != metConditions
        {
            // The conditions have not been met. Fire the next time they are.
            iConditions.conditions[i].hasFired = false;
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
