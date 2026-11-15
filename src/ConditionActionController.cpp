// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include "ConditionActionController.h"
#include "TimeController.h"
#include "ActionController.h"

// TEMP
#include "FileHandler.h"
// TEMP

CConditionActionController *CConditionActionController::iInstance = NULL;

// Run the main condition-action loop
void CConditionActionController::RunLoopL()
{
    // TEST CODE
    // Create a simple time condition for testing
    //iConditions.conditions = new(ELeave) struct Condition[1];

    //iConditions.conditions[0].timeCondition = new(ELeave) struct TimeCondition;

    //iConditions.conditions[0].timeCondition->time.SetYear(2026);
    //iConditions.conditions[0].timeCondition->used = BIT(KTIME_USED_YEAR_BIT);

    //iConditions.conditions[0].vibrationAction = new(ELeave) struct VibrationAction;
    //iConditions.conditions[0].vibrationAction->duration = 3000;
    //iConditions.conditions[0].vibrationAction->intensity = 100;

    //iConditions.count = 1;

    // Save the condition data to file for testing
    //_LIT(KFilename, "c:\\cutcrosstest.bin");
    //CFileHandler *fileHandler = CFileHandler::GetInstanceL();
    //fileHandler->SaveConditionDataL(&iConditions, KFilename);

    // Load the condition data from file for testing
    _LIT(KFilename, "c:\\cutcrosstest.bin");
    CFileHandler *fileHandler = CFileHandler::GetInstanceL();
    iConditions = fileHandler->LoadConditionDataL(KFilename);
    // TEST CODE

    // Condition and action controllers
    CTimeController *timeController = CTimeController::GetInstanceL();
    CActionController *actionController = CActionController::GetInstanceL();

    //actionController->VibrateL(10000, 100); // TEST
    // Loop forever until something deliberately breaks out of the loop
    // TODO: Currently only run once, until condition-action functionality is separated from UI and daemonised.
    //while(true)
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
