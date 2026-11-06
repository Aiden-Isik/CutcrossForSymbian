// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#include "ActionController.h"

CActionController::CActionController()
{
}

CActionController::~CActionController()
{
}

CActionController* CActionController::NewLC()
{
    CActionController* self = new (ELeave) CActionController();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}

CActionController* CActionController::NewL()
{
    CActionController* self = CActionController::NewLC();
    CleanupStack::Pop(); // self;
    return self;
}

void CActionController::ConstructL()
{
}
