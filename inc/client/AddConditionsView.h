// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef ADDCONDITIONSVIEW_H_
#define ADDCONDITIONSVIEW_H_

#include <e32std.h>
#include <e32base.h>
#include <aknlists.h>
#include <coedef.h>
#include <coecntrl.h>
#include <eiklbo.h>
#include <eiklbx.h>
#include <http.h>

#include "View.h"
#include "ConditionActionData.h"

class CAddConditionsView: public CView, public MEikListBoxObserver
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
        static CAddConditionsView *NewL(const TRect &aRect);
        static CAddConditionsView *NewLC(const TRect &aRect);

        // Destructor
        ~CAddConditionsView();

    protected:
        // Controls
        CAknSingleStyleListBox *iListBox;

        // Constructors
        CAddConditionsView();
        void ConstructL(const TRect &aRect);

    private:
        // Conditions to write
        Conditions iConditions;

        // Hex string handling
        TBool BufferIsHex(TDesC &aBuffer);
        TUint64 HexToU64L(TDesC &aBuffer);
};

#endif /* ADDCONDITIONSVIEW_H_ */
