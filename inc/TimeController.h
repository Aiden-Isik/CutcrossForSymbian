// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#ifndef TIMECONTROLLER_H
#define TIMECONTROLLER_H

#include <e32std.h>
#include <e32base.h>

class CTimeController: public CBase
{
    public:
        // Stand-in constructor
        static CActionController *GetInstanceL;

        // Update the stored time
        void UpdateTime();

        // Retrieve the stored time
        TDateTime GetTime();

    private:
        // The singleton object created from this class
        // Initialised to NULL as per C++ standard for static variables
        static CActionController *iInstance;

        // Constructor
        CTimeController();
};

#endif // TIMECONTROLLER_H
