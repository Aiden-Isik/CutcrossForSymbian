// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#include <unistd.h>

#include <aknnotewrappers.h>
#include <aknglobalnote.h>
#include <hwrmvibra.h>

#include "ActionController.h"

CActionController *CActionController::iInstance = NULL;

// Send global notification
void CActionController::SendGlobalNotificationL(TDesC &aBodyText)
{
    // Send the notification
    CAknGlobalNote *notification = CAknGlobalNote::NewLC(); // Added to cleanup stack
    TInt notificationId = notification->ShowNoteL(EAknGlobalInformationNote, aBodyText);
    
    // Sleep for 5 seconds to allow the user to see the notification.
    // This will block the thread and therefore the whole condition-action loop.
    // Multithreading may be implemented at a later date to prevent this,
    // although for reasonable use-cases it is not a big deal (and multithreading
    // may carry a vital resource usage penalty on such weak hardware).
    sleep(5);
    
    // Delete the notification
    notification->CancelNoteL(notificationId);
    CleanupStack::PopAndDestroy(); // Pop the notification off the cleanup stack, it's gone
}

// Run the vibration motor
// Duration is in ms, intensity is between -100 and 100 (as a percentage)
void CActionController::VibrateL(TUint16 aDuration, TInt8 aIntensity)
{
    // Verify that the intensity falls between the valid range of -100 to 100
    // TODO: Ensure this is absolutely correct
    if(aIntensity < -100 || aIntensity > 100)
    {
        // Leave with invalid argument
        User::Leave(KErrArgument);
    }

    // Set the vibration motor to vibrate for a set length of time and intensity
    CHWRMVibra *vibrationMotor = CHWRMVibra::NewLC(); // Added to cleanup stack
    vibrationMotor->StartVibraL(aDuration, aIntensity);

    // Sleep for at least as long as the motor is set to run (in seconds).
    sleep((aDuration / 1000) + 1);

    // Cleanup
    CleanupStack::PopAndDestroy(); // Pop the vibration motor off the cleanup stack.
}

// Constructor
// Unused
CActionController::CActionController()
{
}

// Stand-in constructor
// This should be called in place of the standard constructor, to enforce
// only one object for this class (singleton)
CActionController *CActionController::GetInstanceL()
{
    if(iInstance == NULL)
    {
        // NOTE: there is no need to deal with the cleanup stack here,
        // as this is a static method.
        iInstance = new(ELeave) CActionController();
    }
    
    return iInstance;
}
