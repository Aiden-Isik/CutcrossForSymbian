// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef MAINVIEW_H_
#define MAINVIEW_H_

#include <e32std.h>
#include <e32base.h>
#include <aknlists.h>
#include <coedef.h>
#include <coecntrl.h>

#include "View.h"

class CMainView: public CView, public MEikListBoxObserver
{
    public:
        // Draw the contents of this view
        void Draw(const TRect &aRect) const;

        // Handle change in size
        void SizeChanged();

        // Component control handling
        CCoeControl *ComponentControl(TInt aIndex) const;
        void HandleListBoxEventL(CEikListBox *aListBox, TListBoxEvent aEvent);

        // Handle key presses
        TKeyResponse OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType);

        // Constructors
        static CMainView *NewL(const TRect &aRect);
        static CMainView *NewLC(const TRect &aRect);

        // Destructor
        ~CMainView();

    protected:
        // Controls
        CAknSingleStyleListBox *iListBox;

        // Constructors
        CMainView();
        void ConstructL(const TRect &aRect);
};

#endif /* MAINVIEW_H_ */
