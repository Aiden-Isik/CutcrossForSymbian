// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <eikapp.h>
#include <eikappui.h>

#include "Document.h"
#include "AppUi.h"

// Constructs the application controller
CEikAppUi *CDocument::CreateAppUiL()
{
    return new(ELeave) CAppUi;
}

// Inherit the CAknDocument default constructor
CDocument::CDocument(CEikApplication &aApp): CAknDocument(aApp)
{
}

// Two-phase constructors
void CDocument::ConstructL()
{
}

CDocument *CDocument::NewL(CEikApplication &aApp)
{
    CDocument *self = new (ELeave)CDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
}
