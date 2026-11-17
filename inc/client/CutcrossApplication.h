// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef CUTCROSSAPPLICATION_H
#define CUTCROSSAPPLICATION_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknapp.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Constants]
const TUid KUidCutcrossApplication = { 0x27B05414 };
// ]]] end generated region [Generated Constants]

/**
 *
 * @class	CCutcrossApplication CutcrossApplication.h
 * @brief	A CAknApplication-derived class is required by the S60 application 
 *          framework. It is subclassed to create the application's document 
 *          object.
 */
class CCutcrossApplication: public CAknApplication
{
    private:
        TUid AppDllUid() const;
        CApaDocument* CreateDocumentL();
};

#endif // CUTCROSSAPPLICATION_H		
