// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <coecntrl.h>

#include "MainView.h"

// Draw the contents of this view
void CMainView::Draw(const TRect &aRect) const
{
    // Get the system graphics context and clear the view rectangle
    CWindowGc &graphicsContext = SystemGc();
    graphicsContext.Clear(aRect);
}

// Constructors
CMainView::CMainView()
{
}

void CMainView::ConstructL(const TRect &aRect)
{
    // Create the window
    CreateWindowL();
    SetRect(aRect); // Set its size
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
