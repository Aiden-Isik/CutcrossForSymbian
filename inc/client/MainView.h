// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef MAINVIEW_H_
#define MAINVIEW_H_

#include <e32std.h>
#include <e32base.h>
#include <aknlists.h>
#include <coedef.h>
#include <coecntrl.h>

class CMainView: public CCoeControl
{
    public:
        // Draw the contents of this view
        void Draw(const TRect &aRect) const;

        // Component control handling
        TInt CountComponentControls() const;
        CCoeControl *ComponentControl(TInt aIndex) const;

        // Handle key presses
        TKeyResponse OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType);

        // Two-phase constructors
        static CMainView *NewL(const TRect &aRect);
        static CMainView *NewLC(const TRect &aRect);

    private:
        // Controls
        TInt iControlCount;
        CAknSingleStyleListBox *iListBox;

        // Constructors
        CMainView();
        void ConstructL(const TRect &aRect);
};

#endif /* MAINVIEW_H_ */
