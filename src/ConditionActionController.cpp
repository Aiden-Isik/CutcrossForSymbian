// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include "ConditionActionController.h"
#include "ActionController.h"
#include "ConditionController.h"

// Run the main condition-action loop
void CConditionActionController::RunLoop()
{
    // Loop forever until something deliberately breaks out of the loop
    while(true)
    {
        // We have a member struct called iConditions which contains information about every
        // set of conditions set up by the user. For every set, check if the condition has been met,
        // and if it has, fire the associated actions.
        for(TUint16 i = 0; i < iConditions.count; i++)
        {
            
        }
    }
}

// Stand-in constructor
// This should be called in place of the standard constructor, to enforce
// only one object for this class (singleton)
static *CConditionActionController::GetInstanceL()
{
    if(iInstance == NULL)
    {
        // NOTE: there is no need to deal with the cleanup stack here,
        // as this is a static method.
        iInstance = new(ELeave) CConditionActionController();
    }
    
    return iInstance;
}

// Enforce only one object for this class (singleton)
CConditionActionController::CConditionActionController(const CConditionActionController&) = delete;
CConditionActionController &CConditionActionController::operator=(const CConditionActionController&) = delete;
