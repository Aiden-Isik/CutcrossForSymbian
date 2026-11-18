// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <akndoc.h>
#include <eikapp.h>
#include <eikappui.h>

class CDocument: public CAknDocument
{
    public:
        // Called by UI framework to create AppUi object
        CEikAppUi *CreateAppUiL();

        // Two-phase constructor
        static CDocument *NewL(CEikApplication &aApp);

    private:
        // Constructors
        void ConstructL();
        CDocument(CEikApplication &aApp);
};

#endif /* DOCUMENT_H_ */
