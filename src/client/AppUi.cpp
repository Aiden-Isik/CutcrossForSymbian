// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <aknappui.h>
#include <eikappui.h>

#include "AppUi.h"
#include "MainView.h"

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
    return;
}
