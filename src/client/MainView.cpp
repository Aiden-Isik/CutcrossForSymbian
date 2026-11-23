// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <e32std.h>
#include <e32cmn.h>
#include <e32base.h>
#include <w32std.h>
#include <aknlists.h>
#include <coedef.h>
#include <coecntrl.h>

#include <avkon.hrh>

#include "View.h"
#include "MainView.h"
#include "AppUi.h"
#include "SaveConditionAction.h"

// Draw the contents of this view
void CMainView::Draw(const TRect &aRect) const
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

// Handle key events
TKeyResponse CMainView::OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType)
{
    // Forward keys to the ListBox
    if(iListBox)
    {
        return iListBox->OfferKeyEventL(aKeyEvent, aType);
    }

    return EKeyWasNotConsumed;
}

// Handle view size changes
void CMainView::SizeChanged()
{
    if(iListBox)
    {
        iListBox->SetRect(Rect());
    }
}

// Handle commands from the application framework
void CMainView::HandleCommandL(TInt aCommand)
{
    switch(aCommand)
    {
        case EMainDelete:
        {
            // Delete selected item
            CSaveConditionAction *saveConditionAction = CSaveConditionAction::GetInstanceL();
            saveConditionAction->DeleteConditionL(iListBox->CurrentItemIndex());

            // Save changes
            saveConditionAction->SaveConditionsToFileL();
            break;
        }
    }
}

// Return a control based on an index
CCoeControl *CMainView::ComponentControl(TInt aIndex) const
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
void CMainView::HandleListBoxEventL(CEikListBox *aListBox, TListBoxEvent aEvent)
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
                    
                }
            }
        }
    }
}

// Constructors
CMainView::CMainView()
{
}

CMainView *CMainView::NewL(const TRect &aRect)
{
    CMainView *self = CMainView::NewLC(aRect);
    CleanupStack::Pop(); // NewLC
    return self;
}

CMainView *CMainView::NewLC(const TRect &aRect)
{
    CMainView *self = new(ELeave) CMainView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self; // Will be popped off the cleanup stack by NewL
}

void CMainView::ConstructL(const TRect &aRect)
{
    // Set the ID for this view
    id = EPageMainId;

    // Create the window
    CreateWindowL();

    // Set up child controls
    iControlCount = 0;

    // Main ListBox
    iListBox = new(ELeave) CAknSingleStyleListBox();
    CleanupStack::PushL(iListBox);
    iListBox->ConstructL(this, EAknListBoxSelectionList);
    iListBox->SetContainerWindowL(*this);
    iListBox->SetExtent(TPoint(0,0), iListBox->MinimumSize());

    // Set up condition-action save class
    CSaveConditionAction *saveConditionAction = CSaveConditionAction::GetInstanceL();
    saveConditionAction->InitialiseUnsavedL();
    saveConditionAction->InitialiseConditionsL();

    // Show loaded condition-action pairs
    struct Conditions *conditions = saveConditionAction->GetConditions();
    CDesCArray *listBoxItems = new(ELeave) CDesCArrayFlat(1); // Granularity of 1, we expect an arbitrary number of items
    CleanupStack::PushL(listBoxItems);

    for(TUint16 i = 0; i < conditions->count; i++)
    {
        // 7 is the max size our string will take, '\t#' + max '65536'
        TBuf<7> itemString;
        itemString.Format(_L("\t#%d"), i + 1);

        // Create the ListBox item
        listBoxItems->AppendL(itemString);
    }

    // Finalise setting up ListBox
    iListBox->Model()->SetItemTextArray(listBoxItems);
    iListBox->Model()->SetOwnershipType(ELbmOwnsItemArray); // ListBox owns the item array memory now
    CleanupStack::Pop(); // listBoxItems
    iListBox->HandleItemAdditionL();
    iListBox->SetListBoxObserver(this);
    CleanupStack::Pop(); // iListBox
    iControlCount++;

    SetRect(aRect); // Set window size
    ActivateL();
}

// Destructor
CMainView::~CMainView()
{
    if(iListBox)
    {
        delete iListBox;
    }
}
