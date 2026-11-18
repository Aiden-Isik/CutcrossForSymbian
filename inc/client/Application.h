// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <e32cmn.h>
#include <aknapp.h>
#include <apparc.h>

class CApplication: public CAknApplication
{
    public:
        // Get the client UID
        TUid AppDllUid() const;

    protected:
        // Create a document, called by the application framework
        CApaDocument *CreateDocumentL();
};

#endif /* APPLICATION_H_ */
