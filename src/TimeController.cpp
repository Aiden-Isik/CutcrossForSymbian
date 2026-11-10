// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#include "TimeController.h"

// Store the current date/time
// We run each controller *once* per condition-action cycle,
// so that all functions to the OS to get the current time, for example,
// are only called once per cycle (rather than calling for every action
// which depends on the current time as a condition).
TDateTime time;

// Update the stored time
void CTimeController::UpdateTime()
{
    // Retrieve the current user-facing time from the OS
    TTime insecureSysTime;
    insecureSysTime.HomeTime();
    
    // Convert the system TTime format to TDateTime,
    // for standard day, hour, minute, etc fields
    time = insecureSysTime.DateTime();
}

// Retrieve the stored time
TDateTime CTimeController::GetTime()
{
    return time;
}

// Constructor
CTimeController::CTimeController()
{
    // Set the initial date/time
    UpdateTime();
}

// Stand-in constructor
// This should be called in place of the standard constructor, to enforce
// only one object for this class (singleton)
static *CTimeController::GetInstanceL()
{
    if(iInstance == NULL)
    {
        // NOTE: there is no need to deal with the cleanup stack here,
        // as this is a static method.
        iInstance = new(ELeave) CTimeController();
    }
    
    return iInstance;
}

// Enforce only one object for this class (singleton)
CTimeController::CTimeController(const CTimeController&) = delete;
CTimeController &CTimeController::operator=(const CTimeController&) = delete;
