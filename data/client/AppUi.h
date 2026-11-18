// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef APPUI_H_
#define APPUI_H_

#include <e32def.h>
#include <aknappui.h>
#include <coecntrl.h>

// We're creating a traditional Avkon application, so we inherit from CAknAppUi.
class CAppUi: public CAknAppUi
{
    public:
        // Command handler
        void HandleCommandL(TInt aCommand);

        // Constructors
        CAppUi();
        void ConstructL();

        // Destructor
        ~CAppUi();

    private:
        CCoeControl *iView;
};

#endif /* APPUI_H_ */
