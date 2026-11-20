// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef VIEW_H_
#define VIEW_H_

#include <e32def.h>
#include <e32std.h>
#include <coecntrl.h>

enum TViewId
{
    EPageMainId = 1,
    EPageAddId,
    EPageAddConditionsId,
    EPageAddActionsId,
};

class CView: public CCoeControl
{
    public:
        // Getters
        TUint8 GetId();

        // Count component controls
        TInt CountComponentControls() const;

        // Two-phase constructors
        static CView *NewL(const TRect &aRect);
        static CView *NewLC(const TRect &aRect);

        // Destructor
        ~CView();

    protected:
        // Control count
        TInt iControlCount;

        // Page ID
        TUint8 id;

        // Constructors
        void ConstructL(const TRect &aRect);
        CView();
};

#endif /* VIEW_H_ */
