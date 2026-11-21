// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <aknlists.h>
#include <coedef.h>
#include <coecntrl.h>
#include <badesca.h>
#include <eikscrlb.h>
#include <eikenv.h>

#include <avkon.hrh>

#include "View.h"
#include "AddView.h"
#include "AppUi.h"

// Defines the ordering of the ListBox items
enum TListBoxItems
{
    EListBoxItemAddConditions = 0,
    EListBoxItemAddActions,
};

// Draw the contents of this view
void CAddView::Draw(const TRect &aRect) const
{
    // Get the system graphics context
    CWindowGc &graphicsContext = SystemGc();

    // Draw rectangle to screen
    graphicsContext.Clear(aRect);

    // Draw the main ListBox if it exists
    if(iListBox)
    {
        iListBox->Draw(aRect);
    }
}

void CAddView::SizeChanged()
{
    if(iListBox)
    {
        iListBox->SetRect(Rect());
    }
}

// Handle key events
TKeyResponse CAddView::OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType)
{
    // Forward keys to the ListBox
    if(iListBox)
    {
        return iListBox->OfferKeyEventL(aKeyEvent, aType);
    }

    return EKeyWasNotConsumed;
}

// Return a control based on an index
CCoeControl *CAddView::ComponentControl(TInt aIndex) const
{
    switch(aIndex)
    {
        case 0:
            return iListBox;
            
        default:
            return NULL;
    }
}

// Handle list box item selections
void CAddView::HandleListBoxEventL(CEikListBox *aListBox, TListBoxEvent aEvent)
{
    switch(aEvent)
    {
        case EEventEnterKeyPressed:
        case EEventItemDoubleClicked:
        {
            // Send the appropriate command back up the chain to CAppUi
            if(iListBox)
            {
                switch(iListBox->CurrentItemIndex())
                {
                    case EListBoxItemAddConditions:
                    {
                        ((CAppUi*)ControlEnv()->AppUi())->HandleCommandL(ESwitchPageAddConditions);
                        break;
                    }
                    case EListBoxItemAddActions:
                    {
                        ((CAppUi*)ControlEnv()->AppUi())->HandleCommandL(ESwitchPageAddActions);
                        break;
                    }
                }
            }
        }
    }
}

// Constructors
CAddView::CAddView()
{
}

CAddView *CAddView::NewL(const TRect &aRect)
{
    CAddView *self = CAddView::NewLC(aRect);
    CleanupStack::Pop(); // NewLC
    return self;
}

CAddView *CAddView::NewLC(const TRect &aRect)
{
    CAddView *self = new(ELeave) CAddView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self; // Will be popped off the cleanup stack by NewL
}

void CAddView::ConstructL(const TRect &aRect)
{
    // Set the ID for this view
    id = EPageAddId;

    // Create the window
    CreateWindowL();

    // Set up child controls
    iControlCount = 0;

    // Main ListBox
    iListBox = new(ELeave) CAknSingleStyleListBox();
    CleanupStack::PushL(iListBox);
    iListBox->SetContainerWindowL(*this);
    iListBox->ConstructL(this, EAknListBoxSelectionList);

    // Make it scrollable (horizontal off, vertical if required)
    iListBox->CreateScrollBarFrameL(ETrue);
    iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
    iListBox->SetExtent(TPoint(0,0), iListBox->MinimumSize());

    // Add condition and action list items
    CDesCArray *listBoxItems = new(ELeave) CDesCArrayFlat(2); // Granularity of 2, so it expects a multiple of 2
    CleanupStack::PushL(listBoxItems);
    listBoxItems->InsertL(EListBoxItemAddConditions, _L("\tSet conditions"));
    listBoxItems->InsertL(EListBoxItemAddActions, _L("\tSet actions"));
    iListBox->Model()->SetItemTextArray(listBoxItems);
    iListBox->Model()->SetOwnershipType(ELbmOwnsItemArray); // ListBox owns the item array memory now
    CleanupStack::Pop(); // listBoxItems
    iListBox->HandleItemAdditionL();

    // Finish up ListBox setup
    iListBox->SetListBoxObserver(this);
    CleanupStack::Pop(); // iListBox
    iControlCount++;

    SetRect(aRect); // Set window size
    ActivateL();
}

// Destructor
CAddView::~CAddView()
{
    if(iListBox)
    {
        delete iListBox;
    }
}
