// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include <e32std.h>
#include <e32base.h>

class CActionController: public CBase
{
    public:
        // Send global notification
        void SendGlobalNotificationL(string aBodyText);

        // Run the vibration motor
        void VibrateL(TUint aDuration, TInt8 aIntensity);

        // Destructor
        ~CActionController();

        // Symbian two-phase constructors
        static CActionController* NewL();
        static CActionController* NewLC();

    private:
        // First-phase constructor
        CActionController();

        // EPOC two-phase constructor
        void ConstructL();

};

#endif // ACTIONCONTROLLER_H
