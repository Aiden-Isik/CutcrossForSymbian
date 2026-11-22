// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#include <e32std.h>
#include <e32cmn.h>

#include "SaveConditionAction.h"
#include "ConditionActionData.h"
#include "FileHandler.h"
#include "Bit.h"

CSaveConditionAction *CSaveConditionAction::iInstance = NULL;
Condition *CSaveConditionAction::iUnsavedCondition = NULL;
Conditions *CSaveConditionAction::iConditions = NULL;

// Clear unsaved condition-action
void CSaveConditionAction::ClearUnsaved()
{
    if(iUnsavedCondition)
    {
        // Conditions
        if(iUnsavedCondition->timeCondition)
        {
            delete iUnsavedCondition->timeCondition;
            iUnsavedCondition->timeCondition = NULL;
        }

        // Actions
        if(iUnsavedCondition->vibrationAction)
        {
            delete iUnsavedCondition->vibrationAction;
            iUnsavedCondition->vibrationAction = NULL;
        }

        delete iUnsavedCondition;
        iUnsavedCondition = NULL;
    }
}

// Initialise unsaved condition-action
void CSaveConditionAction::InitialiseUnsavedL()
{
    // Make sure any old data is cleared
    ClearUnsaved();

    // Allocate condition-action
    iUnsavedCondition = new(ELeave) Condition;
    memset(iUnsavedCondition, 0, sizeof(Condition));
}

void CSaveConditionAction::AddUnsavedConditionDateL(TUint16 aYear, TUint8 aMonth, TUint8 aDay, TUint8 aUsed)
{
    // Initialise unsaved condition if it isn't already
    if(!iUnsavedCondition)
    {
        InitialiseUnsavedL();
    }

    // Allocate memory for date-time conditions if required
    if(!iUnsavedCondition->timeCondition)
    {
        iUnsavedCondition->timeCondition = new(ELeave) TimeCondition;

        // Make sure time field bitfield is zeroed
        iUnsavedCondition->timeCondition->used = 0;
    }

    // Clear date part of the time bitfield
    TUint8 *used = &(iUnsavedCondition->timeCondition->used);
    TUint8 dateFieldsMask = BIT(KTIME_USED_YEAR_BIT) | BIT(KTIME_USED_MONTH_BIT) | BIT(KTIME_USED_DAY_BIT);
    *used &= ~dateFieldsMask;

    // Set dates
    TDateTime *date = &(iUnsavedCondition->timeCondition->time);

    if(BITFIELD_BIT(aUsed, KTIME_USED_YEAR_BIT))
    {
        User::LeaveIfError(date->SetYear(aYear));
    }

    if(BITFIELD_BIT(aUsed, KTIME_USED_MONTH_BIT))
    {
        User::LeaveIfError(date->SetMonth((TMonth)(aMonth - 1))); // January is encoded as 0, February 1, etc
    }

    if(BITFIELD_BIT(aUsed, KTIME_USED_DAY_BIT))
    {
        User::LeaveIfError(date->SetDay(aDay));
    }

    // Finally, set the appropriate used bits in the time bitfield
    *used |= (aUsed & dateFieldsMask);
}

void CSaveConditionAction::AddUnsavedConditionTimeL(TUint8 aHour, TUint8 aMinute, TUint8 aUsed)
{
    // Initialise unsaved condition if it isn't already
    if(!iUnsavedCondition)
    {
        InitialiseUnsavedL();
    }

    // Allocate memory for date-time conditions if required
    if(!iUnsavedCondition->timeCondition)
    {
        iUnsavedCondition->timeCondition = new(ELeave) TimeCondition;

        // Make sure time field bitfield is zeroed
        iUnsavedCondition->timeCondition->used = 0;
    }

    // Clear time part of the time bitfield
    TUint8 *used = &(iUnsavedCondition->timeCondition->used);
    TUint8 timeFieldsMask = BIT(KTIME_USED_HOUR_BIT) |
                            BIT(KTIME_USED_MINUTE_BIT) |
                            BIT(KTIME_USED_SECOND_BIT) |
                            BIT(KTIME_USED_MICROSECOND_BIT);
    *used &= ~timeFieldsMask;

    // Set times
    TDateTime *time = &(iUnsavedCondition->timeCondition->time);

    if(BITFIELD_BIT(aUsed, KTIME_USED_HOUR_BIT))
    {
        User::LeaveIfError(time->SetHour(aHour));
    }

    if(BITFIELD_BIT(aUsed, KTIME_USED_MINUTE_BIT))
    {
        User::LeaveIfError(time->SetMinute(aMinute));
    }

    // Finally, set the appropriate used bits in the time bitfield
    *used |= (aUsed & timeFieldsMask);
}

void CSaveConditionAction::AddUnsavedActionVibrateL(TUint16 aDuration, TInt8 aIntensity)
{
    // Initialise unsaved condition if it isn't already
    if(!iUnsavedCondition)
    {
        InitialiseUnsavedL();
    }

    // Allocate memory for vibration data if required
    if(!iUnsavedCondition->vibrationAction)
    {
        iUnsavedCondition->vibrationAction = new(ELeave) VibrationAction;
    }

    // Check intensity is between -100% and 100%
    if(aIntensity < -100 || aIntensity > 100)
    {
        User::Leave(KErrArgument);
    }

    // Set duration and intensity
    iUnsavedCondition->vibrationAction->duration = aDuration;
    iUnsavedCondition->vibrationAction->intensity = aIntensity;
}

// Initialise all condition-actions
void CSaveConditionAction::InitialiseConditionsL()
{
    // Free any conditions memory which may be in use, to start with a clean slate
    if(iConditions)
    {
        if(iConditions->conditions)
        {
            // Delete all conditions and actions present
            for(TUint16 i = 0; i < iConditions->count; i++)
            {
                if(iConditions->conditions[i].timeCondition)
                {
                    delete iConditions->conditions[i].timeCondition;
                    iConditions->conditions[i].timeCondition = NULL;
                }

                if(iConditions->conditions[i].vibrationAction)
                {
                    delete iConditions->conditions[i].vibrationAction;
                    iConditions->conditions[i].vibrationAction = NULL;
                }
            }

            delete iConditions->conditions;
            iConditions->conditions = NULL;
        }

        delete iConditions;
        iConditions = NULL;
    }

    // Load the save file if possible
    CFileHandler *fileHandler = CFileHandler::GetInstanceL();
    Conditions conditions;
    iConditions = new(ELeave) Conditions;
    TRAPD(error, conditions=fileHandler->LoadConditionDataL(KSaveFileName));

    // If an error was encountered reading the file, create blank condition-actions
    if(error)
    {
        // We failed to read the file. Create a new blank set of conditions and actions
        memset(iConditions, 0, sizeof(Conditions));
    }
    else
    {
        // The file was read successfully, use the data it contained
        memcpy(iConditions, &conditions, sizeof(Conditions));
    }
}

// Constructor
// Unused
CSaveConditionAction::CSaveConditionAction()
{
}

// Stand-in constructor
// This should be called in place of the standard constructor, to enforce
// only one object for this class (singleton)
CSaveConditionAction *CSaveConditionAction::GetInstanceL()
{
    if(iInstance == NULL)
    {
        // NOTE: there is no need to deal with the cleanup stack here,
        // as this is a static method.
        iInstance = new(ELeave) CSaveConditionAction();
    }
    
    return iInstance;
}
