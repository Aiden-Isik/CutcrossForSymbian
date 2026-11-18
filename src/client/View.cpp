// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <e32def.h>
#include <e32base.h>

#include "View.h"

// Get ID
TUint8 CView::GetId()
{
    return id;
}

// Return the count of child controls in this component control
TInt CView::CountComponentControls() const
{
    return iControlCount;
}

// Constructors
CView *CView::NewL(const TRect &aRect)
{
    CView *self = CView::NewLC(aRect);
    CleanupStack::Pop(); // NewLC
    return self;
}

CView *CView::NewLC(const TRect &aRect)
{
    CView *self = new(ELeave) CView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self; // Will be popped off the cleanup stack by NewL
}

void CView::ConstructL(const TRect &aRect)
{
    // Set ID to NULL
    id = NULL;
}

CView::CView()
{
}

// Destructor
CView::~CView()
{
}
