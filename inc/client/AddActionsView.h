// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef ADDACTIONSVIEW_H_
#define ADDACTIONSVIEW_H_

#include <e32std.h>
#include <e32base.h>
#include <aknlists.h>
#include <coedef.h>
#include <coecntrl.h>
#include <eiklbo.h>
#include <eiklbx.h>

#include "View.h"
#include "ConditionActionData.h"

class CAddActionsView: public CView, public MEikListBoxObserver
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
        static CAddActionsView *NewL(const TRect &aRect);
        static CAddActionsView *NewLC(const TRect &aRect);

        // Destructor
        ~CAddActionsView();

    protected:
        // Controls
        CAknSingleStyleListBox *iListBox;

        // Constructors
        CAddActionsView();
        void ConstructL(const TRect &aRect);

    private:
        // Conditions to write
        Conditions iConditions;
};

#endif /* ADDACTIONSVIEW_H_ */
