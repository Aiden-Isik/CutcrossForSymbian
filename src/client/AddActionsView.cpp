// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <e32std.h>
#include <e32base.h>
#include <w32std.h>
#include <aknlists.h>
#include <aknquerydialog.h>
#include <coedef.h>
#include <coecntrl.h>
#include <badesca.h>
#include <eikscrlb.h>
#include <eikenv.h>

#include <avkon.hrh>

#include "View.h"
#include "AddActionsView.h"
#include "AppUi.h"
#include "SaveConditionAction.h"

#include "Cutcross.rsg"

// Defines the ordering of the ListBox items
enum TListBoxItems
{
    EListBoxItemVibration = 0,
};

// Draw the contents of this view
void CAddActionsView::Draw(const TRect &aRect) const
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

void CAddActionsView::SizeChanged()
{
    if(iListBox)
    {
        iListBox->SetRect(Rect());
    }
}

// Handle key events
TKeyResponse CAddActionsView::OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType)
{
    // Forward keys to the ListBox
    if(iListBox)
    {
        return iListBox->OfferKeyEventL(aKeyEvent, aType);
    }

    return EKeyWasNotConsumed;
}

// Return a control based on an index
CCoeControl *CAddActionsView::ComponentControl(TInt aIndex) const
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
void CAddActionsView::HandleListBoxEventL(CEikListBox *aListBox, TListBoxEvent aEvent)
{
    switch(aEvent)
    {
        case EEventEnterKeyPressed:
        case EEventItemDoubleClicked:
        {
            // Bring up the appropriate prompts
            if(iListBox)
            {
                switch(iListBox->CurrentItemIndex())
                {
                    case EListBoxItemVibration:
                    {
                        // Vibration settings
                        TUint16 duration = 1000; // Default 1s
                        TUint8 intensity = 100; // Default 100%

                        // Request vibration settings
                        // Duration
                        TInt value;
                        CAknNumberQueryDialog *dialog = CAknNumberQueryDialog::NewL(value);

                        if(dialog->ExecuteLD(R_APPLICATION_CUTCROSS_QUERY_ACTION_VIBRATE_DURATION))
                        {
                            duration = value;
                        }

                        // Intensity
                        dialog = CAknNumberQueryDialog::NewL(value);

                        if(dialog->ExecuteLD(R_APPLICATION_CUTCROSS_QUERY_ACTION_VIBRATE_INTENSITY))
                        {
                            intensity = value;
                        }

                        // Set unsaved vibration settings
                        CSaveConditionAction *saveConditionAction = CSaveConditionAction::GetInstanceL();
                        saveConditionAction->AddUnsavedActionVibrateL(duration, intensity);
                        break;
                    }
                }
            }
        }
    }
}

// Constructors
CAddActionsView::CAddActionsView()
{
}

CAddActionsView *CAddActionsView::NewL(const TRect &aRect)
{
    CAddActionsView *self = CAddActionsView::NewLC(aRect);
    CleanupStack::Pop(); // NewLC
    return self;
}

CAddActionsView *CAddActionsView::NewLC(const TRect &aRect)
{
    CAddActionsView *self = new(ELeave) CAddActionsView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self; // Will be popped off the cleanup stack by NewL
}

void CAddActionsView::ConstructL(const TRect &aRect)
{
    // Set the ID for this view
    id = EPageAddConditionsId;

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

    // Add list items for settable conditions
    CDesCArray *listBoxItems = new(ELeave) CDesCArrayFlat(1); // Granularity of 1, we want an arbitrary number of items
    CleanupStack::PushL(listBoxItems);
    listBoxItems->InsertL(EListBoxItemVibration, _L("\tVibration"));
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
CAddActionsView::~CAddActionsView()
{
    if(iListBox)
    {
        delete iListBox;
    }
}
