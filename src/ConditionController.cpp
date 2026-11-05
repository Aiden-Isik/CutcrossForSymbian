// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include "ConditionController.h"

void CConditionController::StartLocationControllerL()
{
    // Only start the location controller if it doesn't already exist
    if(!iLocationController)
    {
        iLocationController = new(ELeave) CLocationController();
    }

    return;
}
