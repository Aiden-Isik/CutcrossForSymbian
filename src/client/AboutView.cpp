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
#include "AboutView.h"

// Draw the contents of this view
void CAboutView::Draw(const TRect &aRect) const
{
    // Get the system graphics context
    CWindowGc &graphicsContext = SystemGc();

    // Draw rectangle to screen
    graphicsContext.Clear(aRect);
}

// Handle key events
TKeyResponse CAboutView::OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType)
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
CCoeControl *CAboutView::ComponentControl(TInt aIndex) const
{
    switch(aIndex)
    {
        default:
            return NULL;
    }
}

// Constructors
CAboutView::CAboutView()
{
}

CAboutView *CAboutView::NewL(const TRect &aRect)
{
    CAboutView *self = CAboutView::NewLC(aRect);
    CleanupStack::Pop(); // NewLC
    return self;
}

CAboutView *CAboutView::NewLC(const TRect &aRect)
{
    CAboutView *self = new(ELeave) CAboutView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self; // Will be popped off the cleanup stack by NewL
}

void CAboutView::ConstructL(const TRect &aRect)
{
    // Set the ID for this view
    id = EPageAboutId;

    // Create the window
    CreateWindowL();

    // Set up child controls
    iControlCount = 0;

    // TODO: child controls

    SetRect(aRect); // Set window size
    ActivateL();
}

// Destructor
CAboutView::~CAboutView()
{
}
