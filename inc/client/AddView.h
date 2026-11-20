// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef ADDVIEW_H_
#define ADDVIEW_H_

#include <e32std.h>
#include <e32base.h>
#include <aknlists.h>
#include <coedef.h>
#include <coecntrl.h>
#include <eiklbo.h>
#include <eiklbx.h>

#include "View.h"

class CAddView: public CView, public MEikListBoxObserver
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
        static CAddView *NewL(const TRect &aRect);
        static CAddView *NewLC(const TRect &aRect);

        // Destructor
        ~CAddView();

    protected:
        // Controls
        CAknSingleStyleListBox *iListBox;

        // Constructors
        CAddView();
        void ConstructL(const TRect &aRect);
};

#endif /* ADDVIEW_H_ */
