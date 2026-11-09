// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#include <aknnotewrappers.h>
#include <hwrmvibra.h>

#include "ActionController.h"

// Send global notification
void CActionController::SendGlobalNotificationL(TDesC *aBodyText)
{
    // Send the notification
    CAknGlobalNote *notification;
    notification = new(ELeave) CAknGlobalNote::NewLC(); // Added to cleanup stack
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
void CActionController::VibrateL(TUint aDuration, TInt8 aIntensity)
{
    // Verify that the intensity falls between the valid range of -100 to 100
    if(aIntensity < -100 || aIntensity > 100)
    {
        // Leave with invalid argument
        User::Leave(KErrArgument);
    }

    // Set the vibration motor to vibrate for a set length of time and intensity
    vibrationMotor = new(ELeave) CHWRMVibra::NewLC(); // Added to cleanup stack
    vibrationMotor->StartVibraL(aDuration, aIntensity);

    // Cleanup  
    CleanupStack::PopAndDestroy(); // Pop the vibration motor off the cleanup stack
}

// Constructor
CActionController::CActionController()
{
}

// Destructor
CActionController::~CActionController()
{
}

// Symbian second-phase constructors
CActionController* CActionController::NewLC()
{
    CActionController* self = new (ELeave) CActionController();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}

CActionController* CActionController::NewL()
{
    CActionController* self = CActionController::NewLC();
    CleanupStack::Pop(); // self;
    return self;
}

// EPOC second-phase constructor
void CActionController::ConstructL()
{
}
