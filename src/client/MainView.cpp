// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <aknlists.h>
#include <coedef.h>
#include <coecntrl.h>

#include <avkon.hrh>

#include "View.h"
#include "MainView.h"

// Draw the contents of this view
void CMainView::Draw(const TRect &aRect) const
{
    // Get the system graphics context
    CWindowGc &graphicsContext = SystemGc();

    // Draw rectangle to screen
    graphicsContext.Clear(aRect);

    // Draw the main ListBox if it exists
    if(iListBox)
    {
        iListBox->Draw(aRect);
    }
}

// Handle key events
TKeyResponse CMainView::OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType)
{
    if(aType == EEventKey)
    {
        switch(aKeyEvent.iCode)
        {

        }
    }

    return EKeyWasNotConsumed;
}

// Return a control based on an index
CCoeControl *CMainView::ComponentControl(TInt aIndex) const
{
    switch(aIndex)
    {
        case 0:
            return iListBox;
            
        default:
            return NULL;
    }
}

// Constructors
CMainView::CMainView()
{
}

CMainView *CMainView::NewL(const TRect &aRect)
{
    CMainView *self = CMainView::NewLC(aRect);
    CleanupStack::Pop(); // NewLC
    return self;
}

CMainView *CMainView::NewLC(const TRect &aRect)
{
    CMainView *self = new(ELeave) CMainView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self; // Will be popped off the cleanup stack by NewL
}

void CMainView::ConstructL(const TRect &aRect)
{
    // Set the ID for this view
    id = EPageMainId;

    // Create the window
    CreateWindowL();

    // Set up child controls
    iControlCount = 0;

    // Main ListBox
    iListBox = new(ELeave) CAknSingleStyleListBox();
    CleanupStack::PushL(iListBox);
    iListBox->ConstructL(this, EAknListBoxSelectionList);
    iListBox->SetContainerWindowL(*this);
    iListBox->SetExtent(TPoint(0,0), iListBox->MinimumSize());
    CleanupStack::Pop(); // iListBox
    iControlCount++;

    SetRect(aRect); // Set window size
    ActivateL();
}

// Destructor
CMainView::~CMainView()
{
    if(iListBox)
    {
        delete iListBox;
    }
}
