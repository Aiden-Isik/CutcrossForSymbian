// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef APPUI_H_
#define APPUI_H_

#include <e32def.h>
#include <aknappui.h>
#include <eikmenup.h>
#include <coecntrl.h>

#include "View.h"
#include "ConditionActionData.h"

enum TViewCommand
{
    ESwitchPageMain = 1000,
    ESwitchPageAbout,
    ESwitchPageAdd,
    ESwitchPageAddConditions,
    ESwitchPageAddActions,
    EAddSave,
    EMainDelete,
};

// We're creating a traditional Avkon application, so we inherit from CAknAppUi.
class CAppUi: public CAknAppUi
{
    public:
        // Command handler
        void HandleCommandL(TInt aCommand);

        // Option menu population function
        void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane *aMenuPage);

        // Constructors
        CAppUi();
        void ConstructL();

        // Destructor
        ~CAppUi();

    private:
        // Default view
        CView *iView;

        // Previous view, kept so it isn't deleted whilst still active
        CView *iPreviousView;

        // Switch the current view
        void SwitchViewL(TUint8 id);

        // Show the about dialog
        void ShowAboutDialogL();
};

#endif /* APPUI_H_ */
