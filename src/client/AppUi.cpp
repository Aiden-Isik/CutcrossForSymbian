// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <aknappui.h>
#include <eikappui.h>

#include <e32def.h>

#include <avkon.hrh>

#include "AppUi.h"
#include "MainView.h"

// Handle commands from the application framework
void CAppUi::HandleCommandL(TInt aCommand)
{
    switch(aCommand)
    {
        case EAknSoftkeyExit:
        case EEikCmdExit:
        {
            Exit();
            break; // We should never get here, but if we do handle it gracefully
        }
        default:
        {
            // We don't have a handler for this command, send it up the chain
            CAknAppUi::HandleCommandL(aCommand);
            break;
        }
            
    }
}

// Constructors
CAppUi::CAppUi()
{
}

void CAppUi::ConstructL()
{
    // Initialise base UI with theme support, which is a requirement
    // for S60v2 FP3 and later, for certain controls to render properly.
    BaseConstructL(EAknEnableSkin);

    // Create default view object
    iView = CMainView::NewL(ClientRect());
    iView->SetMopParent(this); // Owned by this object
    AddToStackL(iView);
    return;
}

// Destructor
CAppUi::~CAppUi()
{
    if(iView)
    {
        // Delete active view
        RemoveFromStack(iView);
        delete iView;
    }
}
