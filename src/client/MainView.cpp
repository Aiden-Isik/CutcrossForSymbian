// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <aknlists.h>
#include <coecntrl.h>

#include <avkon.hrh>

#include "MainView.h"

// Draw the contents of this view
void CMainView::Draw(const TRect &aRect) const
{
    // Get the system graphics context
    CWindowGc &graphicsContext = SystemGc();

    // Draw the main ListBox if it exists
    if(iListBox)
    {
        iListBox->Draw(aRect);
    }

    // Draw rectangle to screen
    graphicsContext.Clear(aRect);
}

// Return the count of child controls in this component control
TInt CMainView::CountComponentControls() const
{
    return iControlCount;
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

void CMainView::ConstructL(const TRect &aRect)
{
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
    CleanupStack::Pop(iListBox);
    iControlCount++;

    SetRect(aRect); // Set window size
    ActivateL();
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
