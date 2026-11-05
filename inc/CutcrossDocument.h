// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef CUTCROSSDOCUMENT_H
#define CUTCROSSDOCUMENT_H

#include <akndoc.h>

class CEikAppUi;

/**
 * @class	CCutcrossDocument CutcrossDocument.h
 * @brief	A CAknDocument-derived class is required by the S60 application 
 *           framework. It is responsible for creating the AppUi object. 
 */
class CCutcrossDocument: public CAknDocument
{
    public:
        // constructor
        static CCutcrossDocument* NewL(CEikApplication& aApp);

        // from base class CEikDocument
        CEikAppUi* CreateAppUiL();

    private:
        // constructors
        CCutcrossDocument(CEikApplication& aApp);
        void ConstructL();
};

#endif // CUTCROSSDOCUMENT_H
