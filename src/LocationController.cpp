// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

// This file contains code to handle location-related conditions

#include <e32def.h>
#include <e32err.h>
#include <lbs.h>

#include "LocationController.h"

// Structure definitions
struct modules
{
        TBool spinLock; // Will be locked if positioning modules are being updated or read
        TInt count;
        TPositionModuleInfoBase *modules;
};

struct position
{
        TBool writeSpinLock; // Will be locked if position is being updated or wants to be updated
        TUint32 readSemaphore; // Will be > 0 if position is being read
        TReal64 longitude;
        TReal64 latitude;
};

// Structure instances
// These only take up more than 4 bytes of memory each if they are actually used
struct modules *iModules;
struct position *iPosition;

// Constructor
CLocationController::CLocationController()
{
    // Set all structs to NULL by default
    iModules = NULL;
    iPosition = NULL;
}

// Destructor
CLocationController::~CLocationController()
{
    // Free memory of all the structs.
    // If they don't exist (set to NULL), delete will do nothing.
    delete iModules;
    iModules = NULL;

    delete iPosition;
    iPosition = NULL;
}

// Initialise position struct (latitude/longitude measurement)
void CLocationController::InitPositionL()
{
    if(!iPosition)
    {
        iPosition = new (ELeave) struct position;
    }
}

// Update the latitude/longitude position readings
void CLocationController::UpdatePosition()
{
    // Make sure position struct is initialised
    InitPosition();

    // Spin until the position struct is unlocked from any writes
    while(iPosition->writeSpinLock);

    // Increment the position struct semaphore, so it doesn't get updated whilst we are reading it
    iPosition->readSemaphore++;

    // TODO: actual position update code
    
    // Decrement the position struct semaphore, we're done with it
    iPosition->readSemaphore--;
}

// Initialise positioning modules struct
void CLocationController::InitModulesL()
{
    if(!iModules)
    {
        iModules = new (ELeave) struct modules;
    }
}

// Get an array of all position modules
void CLocationController::SetModulesL()
{
    // Connect to the location server
    RPositionServer server;
    User::LeaveIfError(server.Connect());
    CleanupClosePushL(server);

    // Get module count
    if(server.GetNumModules(iModules->count) <= 0)
    {
        // There are no positioning modules, we cannot support location
        User::Leave( KErrNotSupported);
    }

    // Get all module info
    for(TUint i = 0; i < iModules->count; i++)
    {
        User::LeaveIfError(server.GetModuleInfoByIndex(i, iModules->modules[i]));
    }

    // Close the connection to the server, we're done with it
    CleanupStack::PopAndDestroy(&server);
}
