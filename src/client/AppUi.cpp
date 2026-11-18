// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <aknappui.h>
#include <eikappui.h>
#include <eikmenup.h>

#include <e32def.h>

#include <avkon.hrh>

#include "AppUi.h"
#include "MainView.h"

#include "Cutcross.rsg"

// Handle commands from the application framework
void CAppUi::HandleCommandL(TInt aCommand)
{
    switch(aCommand)
    {
        case EAknSoftkeyExit:
        case EEikCmdExit:
        case ESwitchPageAbout:
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

// Populate options menu based on the current view
void CAppUi::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane *aMenuPane)
{
    if(aResourceId == R_APPLICATION_CUTCROSS_MENU)
    {
        CEikMenuPaneItem::SData newOption;

        switch(iView->GetId())
        {
            case EPageMainId:
            {
                // Add "about" menu item to the main options menu
                newOption.iCommandId = ESwitchPageAbout;
                newOption.iText = _L("About");
                newOption.iCascadeId = 0;
                newOption.iFlags = 0;
                aMenuPane->AddMenuItemL(newOption);
            }
        }

        // Add "exit" menu item
        newOption.iCommandId = EEikCmdExit;
        newOption.iText = _L("Exit");
        newOption.iCascadeId = 0;
        newOption.iFlags = 0;
        aMenuPane->AddMenuItemL(newOption);
    }
    
    CAknAppUi::DynInitMenuPaneL(aResourceId, aMenuPane);
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
