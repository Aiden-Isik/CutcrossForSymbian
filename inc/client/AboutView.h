// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef ABOUTVIEW_H_
#define ABOUTVIEW_H_

#include <e32std.h>
#include <e32base.h>
#include <aknlists.h>
#include <coedef.h>
#include <coecntrl.h>

#include "View.h"

class CAboutView: public CView
{
    public:
        // Draw the contents of this view
        void Draw(const TRect &aRect) const;

        // Component control handling
        CCoeControl *ComponentControl(TInt aIndex) const;

        // Handle control size changes
        void SizeChanged();

        // Handle key presses
        TKeyResponse OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType);

        // Constructors
        static CAboutView *NewL(const TRect &aRect);
        static CAboutView *NewLC(const TRect &aRect);

        // Destructor
        ~CAboutView();

    protected:
        // Constructors
        CAboutView();
        void ConstructL(const TRect &aRect);

    private:
        // Text box
        CEikEdwin *iTextBox;
};

#endif /* ABOUTVIEW_H_ */
