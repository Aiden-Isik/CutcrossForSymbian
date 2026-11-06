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

// Destructor
CTimeController::~CTimeController()
{
}

// Symbian second-phase constructors
CTimeController *CTimeController::NewLC()
{
    CTimeController *self = new (ELeave) CTimeController();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}

CTimeController *CTimeController::NewL()
{
    CTimeController *self = CTimeController::NewLC();
    CleanupStack::Pop(); // self;
    return self;
}

// EPOC second-phase constructor
void CTimeController::ConstructL()
{
}
