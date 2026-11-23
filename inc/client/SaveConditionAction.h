// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#ifndef SAVECONDITIONACTION_H
#define SAVECONDITIONACTION_H

#include <e32std.h>
#include <e32base.h>

#include "ConditionActionData.h"

class CSaveConditionAction: public CBase
{
    public:
        // Stand-in constructor
        static CSaveConditionAction *GetInstanceL();

        // Clear unsaved condition-action
        static void ClearUnsaved();

        // Initialise unsaved condition-action
        static void InitialiseUnsavedL();
        static void AddUnsavedConditionDateL(TUint16 aYear, TUint8 aMonth, TUint8 aDay, TUint8 aUsed);
        static void AddUnsavedConditionTimeL(TUint8 aHour, TUint8 aMinute, TUint8 aUsed);
        static void AddUnsavedActionVibrateL(TUint16 aDuration, TInt8 aIntensity);

        // Initialise all condition-actions
        static void ClearConditions();
        static void InitialiseConditionsL();
        static void AddConditionFromUnsavedL();
        static void DeleteConditionL(TUint16 index);

        // Save to file
        static void SaveConditionsToFileL();

        // Return conditions
        static struct Conditions *GetConditions();

    private:
        // The singleton object created from this class
        // Initialised to NULL as per C++ standard for static variables
        static CSaveConditionAction *iInstance;

        // Unsaved condition-action
        static Condition *iUnsavedCondition;

        // All condition-actions
        static Conditions *iConditions;

        // Constructor
        CSaveConditionAction();
};

#endif // SAVECONDITIONACTION_H
