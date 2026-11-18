// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

// This is the entry point to the Cutcross client.
#include <eikstart.h>

#include "Application.h"

// Function which creates CApplication class,
// address to be passed to EikStart::RunApplication().
LOCAL_C CApaApplication *NewApplication()
{
    return new CApplication;
}

GLDEF_C TInt E32Main()
{
    return EikStart::RunApplication(NewApplication);
}
