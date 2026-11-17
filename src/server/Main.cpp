// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

// This is the entry point to the Cutcross server.
//
// It sets up ways for the client to communicate with it,
// and also runs the main loop.

#include <e32def.h>
#include <e32std.h>
#include <e32base.h>

#include "ConditionActionController.h"
#include "ActionController.h"

void SetupL()
{
    // Set up the active scheduler, to handle async requests from the client
    CActiveScheduler *activeScheduler = new(ELeave) CActiveScheduler();
    CleanupStack::PushL(activeScheduler);
    CActiveScheduler::Install(activeScheduler);
    CleanupStack::PushL(TCleanupItem((TCleanupOperation)CActiveScheduler::Install, NULL));

    // Start up the main condition-action code
    CConditionActionController *conditionActionController = CConditionActionController::GetInstanceL();
    conditionActionController->InitialiseL();

    // TEST: run the condition-action loop once
    conditionActionController->RunLoopL();

    // Cleanup
    CleanupStack::PopAndDestroy(2); // activeScheduler installation, activeScheduler
}

GLDEF_C TInt E32Main()
{
    // Set up leave/trap handling
    CTrapCleanup *cleanup = CTrapCleanup::New();

    // Set up everything else, allowing for standard leaves
    TRAPD(error, SetupL());

    // Cleanup
    delete cleanup;
    return error;
}
