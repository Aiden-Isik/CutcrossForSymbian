// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <e32std.h>
#include <e32base.h>

#include "ConditionActionData.h"

_LIT(KSaveFileName, "c:\\private\\27B05414\\cutcross.bin");

class CFileHandler: public CBase
{
    public:
        // Stand-in constructor
        static CFileHandler *GetInstanceL();

        struct Conditions LoadConditionDataL(const TDesC &aFilename);
        void SaveConditionDataL(const struct Conditions *aConditions, const TDesC &aFilename);

    private:
        // The singleton object created from this class
        // Initialised to NULL as per C++ standard for static variables
        static CFileHandler *iInstance;

        // Constructor
        CFileHandler();
};

#endif // FILEHANDLER_H
