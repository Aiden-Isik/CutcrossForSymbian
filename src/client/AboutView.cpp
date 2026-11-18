// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <coedef.h>
#include <coecntrl.h>
#include <eikedwin.h>

#include <avkon.hrh>

#include "Version.h"
#include "View.h"
#include "AboutView.h"

// Draw the contents of this view
void CAboutView::Draw(const TRect &aRect) const
{
    // Get the system graphics context
    CWindowGc &graphicsContext = SystemGc();

    // Draw the about text box if it exists
    if(iTextBox)
    {
        iTextBox->Draw(aRect);
    }

    // Draw rectangle to screen
    graphicsContext.Clear(aRect);
}

// Handle control size changes
void CAboutView::SizeChanged()
{
    if(iTextBox)
    {
        iTextBox->SetExtent(TPoint(0, 0), Size());
    }
}

// Handle key events
TKeyResponse CAboutView::OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType)
{
    if(aType == EEventKey)
    {
        switch(aKeyEvent.iCode)
        {

        }
    }

    return EKeyWasNotConsumed;
}

// Return a control based on an index
CCoeControl *CAboutView::ComponentControl(TInt aIndex) const
{
    switch(aIndex)
    {
        case 0:
            return iTextBox;
        default:
            return NULL;
    }
}

// Constructors
CAboutView::CAboutView()
{
}

CAboutView *CAboutView::NewL(const TRect &aRect)
{
    CAboutView *self = CAboutView::NewLC(aRect);
    CleanupStack::Pop(); // NewLC
    return self;
}

CAboutView *CAboutView::NewLC(const TRect &aRect)
{
    CAboutView *self = new(ELeave) CAboutView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self; // Will be popped off the cleanup stack by NewL
}

void CAboutView::ConstructL(const TRect &aRect)
{
    // Set the ID for this view
    id = EPageAboutId;

    // Create the window
    CreateWindowL();

    // Set up child controls
    iControlCount = 0;

    // Create an EIKON Edwin instance for the text box
    iTextBox = new(ELeave) CEikEdwin;
    CleanupStack::PushL(iTextBox);
    iTextBox->ConstructL(EEikEdwinReadOnly | EEikEdwinNoHorizScrolling, 0, 0); // 0 == unlimited length, lines
    iTextBox->SetContainerWindowL(*this);

    // Populate the text box
    _LIT(textBoxText, "Cutcross for Symbian S60 3rd Edition+ - Version " KCUTCROSS_VERSION "\n"
                      "Copyright (c) 2026 Aiden Isik <aidenisik@member.fsf.org>\n"
                      "https://github.com/Aiden-Isik/CutcrossForSymbian\n\n"

                      "This program is free software: you can redistribute it and/or modify "
                      "it under the terms of the GNU Affero General Public License as published by "
                      "the Free Software Foundation, either version 3 of the License, or "
                      "(at your option) any later version.\n\n"

                      "This program is distributed in the hope that it will be useful, "
                      "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                      "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the "
                      "GNU Affero General Public License for more details.\n\n"

                      "You should have received a copy of the GNU Affero General Public License "
                      "along with this program.  If not, see <https://www.gnu.org/licenses/>.");
    iTextBox->SetTextL(&textBoxText);
    iTextBox->SetExtent(TPoint(0,0), iTextBox->MinimumSize());
    iTextBox->ActivateL();
    CleanupStack::Pop(); // iTextBox
    iControlCount++;

    SetRect(aRect); // Set window size
    ActivateL();
}

// Destructor
CAboutView::~CAboutView()
{
    if(iTextBox)
    {
        delete iTextBox;
    }
}
