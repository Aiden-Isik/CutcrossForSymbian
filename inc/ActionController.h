// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include <e32std.h>
#include <e32base.h>

class CActionController: public CBase
{
    public:
        // Stand-in constructor
        static CActionController *GetInstanceL();

        // Send global notification
        void SendGlobalNotificationL(string aBodyText);

        // Run the vibration motor
        void VibrateL(TUint aDuration, TInt8 aIntensity);

    private:
        // The singleton object created from this class
        // Initialised to NULL as per C++ standard for static variables
        static CActionController *iInstance;

        // Constructor
        CActionController();
};

#endif // ACTIONCONTROLLER_H
