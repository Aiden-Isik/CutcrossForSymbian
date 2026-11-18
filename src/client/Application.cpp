// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include "Application.h"
#include "Document.h"
#include "Uid.h"

// Get the client UID
TUid CApplication::AppDllUid() const
{
    return TUid::Uid(KUidClient);
}

// Create document, called by application framework.
// It owns our UI controller.
CApaDocument *CApplication::CreateDocumentL()
{
    return CDocument::NewL(*this);
}
