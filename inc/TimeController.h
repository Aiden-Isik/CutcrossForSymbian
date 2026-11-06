// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#ifndef TIMECONTROLLER_H
#define TIMECONTROLLER_H

#include <e32std.h>
#include <e32base.h>

class CTimeController: public CBase
{
    public:
        // Update the stored time
        void UpdateTime();

        // Retrieve the stored time
        TDateTime GetTime();

        // Destructor
        ~CTimeController();

        // Symbian second-phase constructors
        static CTimeController* NewL();
        static CTimeController* NewLC();

    private:
        // First-phase constructor
        CTimeController();

        // EPOC second-phase constructor
        void ConstructL();

};

#endif // TIMECONTROLLER_H
