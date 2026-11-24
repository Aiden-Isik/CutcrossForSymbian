// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#include <e32std.h>
#include <e32cmn.h>
#include <string.h>

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

        if(iUnsavedCondition->bluetoothDeviceCondition)
        {
            delete iUnsavedCondition->bluetoothDeviceCondition;
            iUnsavedCondition->bluetoothDeviceCondition = NULL;
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
        iUnsavedCondition->timeCondition = new(ELeave) struct TimeCondition;

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
    else
    {
        User::LeaveIfError(date->SetMonth(EJanuary)); // Default to January so 31 days are valid
    }

    if(BITFIELD_BIT(aUsed, KTIME_USED_DAY_BIT))
    {
        User::LeaveIfError(date->SetDay(aDay - 1)); // 0-based encoding
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
        iUnsavedCondition->timeCondition = new(ELeave) struct TimeCondition;

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

// Clear all condition-actions
void CSaveConditionAction::ClearConditions()
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

                if(iConditions->conditions[i].bluetoothDeviceCondition)
                {
                    delete iConditions->conditions[i].bluetoothDeviceCondition;
                    iConditions->conditions[i].bluetoothDeviceCondition = NULL;
                }

                if(iConditions->conditions[i].vibrationAction)
                {
                    delete iConditions->conditions[i].vibrationAction;
                    iConditions->conditions[i].vibrationAction = NULL;
                }
            }

            delete[] iConditions->conditions;
            iConditions->conditions = NULL;
        }

        delete iConditions;
        iConditions = NULL;
    }
}

// Initialise all condition-actions
void CSaveConditionAction::InitialiseConditionsL()
{
    ClearConditions();

    // Load the save file if possible
    CFileHandler *fileHandler = CFileHandler::GetInstanceL();
    struct Conditions conditions;
    iConditions = new(ELeave) Conditions;
    TRAPD(error, conditions=fileHandler->LoadConditionDataL(KSaveFileName));

    // If an error was encountered reading the file, create blank condition-actions
    if(error)
    {
        // We failed to read the file. Create a new blank set of conditions and actions
        memset(iConditions, 0, sizeof(struct Conditions));
    }
    else
    {
        // The file was read successfully, use the data it contained
        memcpy(iConditions, &conditions, sizeof(struct Conditions));
    }
}

void CSaveConditionAction::AddConditionFromUnsavedL()
{
    // Make sure conditions and unsaved condition actually exist
    if(!iConditions || !iUnsavedCondition)
    {
        User::Leave(KErrNotFound);
    }

    // Create the new conditions array, which will replace the old one
    TUint16 oldCount = iConditions->conditions ? iConditions->count : 0;
    struct Condition *conditions = new(ELeave) struct Condition[oldCount + 1]; // +1 for new condition
    CleanupStack::PushL(conditions);

    // Copy the current conditions, but only if they actually exist
    if(oldCount > 0)
    {
        memcpy(conditions, iConditions->conditions, sizeof(struct Condition) * oldCount);
    }

    // Append the new condition
    memcpy(&(conditions[oldCount]), iUnsavedCondition, sizeof(struct Condition));

    // Free the old conditions array
    delete[] iConditions->conditions;
    iUnsavedCondition->timeCondition = NULL; // We own these pointers now. Prevent cleanup code from deleting them.
    iUnsavedCondition->bluetoothDeviceCondition = NULL;
    iUnsavedCondition->vibrationAction = NULL;

    // Point the new conditions array to ours, newly appended
    iConditions->conditions = conditions;
    iConditions->count = oldCount + 1;
    CleanupStack::Pop(); // conditions
}

void CSaveConditionAction::DeleteConditionL(TUint16 index)
{
    // Make sure conditions actually exists
    if(!iConditions)
    {
        User::Leave(KErrNotFound);
    }

    // Make sure index exists
    if(index >= iConditions->count)
    {
        User::Leave(KErrArgument);
    }

    // Create the new conditions array to replace the old one
    TUint16 oldCount = iConditions->count;

    if(oldCount > 1)
    {
        struct Condition *conditions = new(ELeave) struct Condition[oldCount - 1];
        CleanupStack::PushL(conditions);

        // Copy everything except the index to delete
        memcpy(conditions, iConditions->conditions, sizeof(struct Condition) * index);
        memcpy(&(conditions[index]), &(iConditions->conditions[index + 1]), sizeof(struct Condition) * (oldCount - index - 1));

        // Free the old conditions array
        delete iConditions->conditions[index].timeCondition;
        delete iConditions->conditions[index].vibrationAction;
        delete iConditions->conditions[index].bluetoothDeviceCondition;
        delete[] iConditions->conditions;

        // Point the new conditions array to ours
        iConditions->conditions = conditions;
        iConditions->count = oldCount - 1;
        CleanupStack::Pop(); // conditions
    }
    else if(oldCount == 1)
    {
        // Just delete the single old condition
        ClearConditions();

        // Then re-initialise it blank
        iConditions = new(ELeave) struct Conditions;
        memset(iConditions, 0, sizeof(struct Conditions));
    }
}

// Save conditions to file
void CSaveConditionAction::SaveConditionsToFileL()
{
    CFileHandler *fileHandler = CFileHandler::GetInstanceL();
    fileHandler->SaveConditionDataL(iConditions, KSaveFileName);
}

struct Conditions *CSaveConditionAction::GetConditions()
{
    return iConditions;
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
