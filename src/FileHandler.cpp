// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include "FileHandler.h"

CFileHandler *CFileHandler::iInstance = NULL;

CFileHandler::CFileHandler()
{
}

// Stand-in constructor
// This should be called in place of the standard constructor, to enforce
// only one object for this class (singleton)
CFileHandler *CFileHandler::GetInstanceL()
{
    if(iInstance == NULL)
    {
        // NOTE: there is no need to deal with the cleanup stack here,
        // as this is a static method.
        iInstance = new(ELeave) CFileHandler();
    }
    
    return iInstance;
}
