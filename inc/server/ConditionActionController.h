// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef CONDITIONACTIONCONTROLLER_H
#define CONDITIONACTIONCONTROLLER_H

#include <e32std.h>
#include <e32base.h>

#include "Bit.h"
#include "ConditionActionData.h"

class CConditionActionController: public CBase
{
    public:
        // Stand-in constructor
        static CConditionActionController *GetInstanceL();

        // Main condition-action loop, the heart of the application
        void RunLoopL();

    private:
        // The singleton object created from this class
        // Initialised to NULL as per C++ standard for static variables
        static CConditionActionController *iInstance;

        // The main conditions struct, holding all conditions and associated actions
        struct Conditions iConditions;

        // Constructor
        CConditionActionController();
};

#endif // CONDITIONACTIONCONTROLLER_H
