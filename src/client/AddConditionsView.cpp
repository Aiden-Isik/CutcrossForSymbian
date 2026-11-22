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
#include "AddConditionsView.h"
#include "AppUi.h"
#include "Bit.h"
#include "SaveConditionAction.h"

#include "Cutcross.rsg"

// Defines the ordering of the ListBox items
enum TListBoxItems
{
    EListBoxItemDate = 0,
    EListBoxItemTime,
};

// Draw the contents of this view
void CAddConditionsView::Draw(const TRect &aRect) const
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

void CAddConditionsView::SizeChanged()
{
    if(iListBox)
    {
        iListBox->SetRect(Rect());
    }
}

// Handle key events
TKeyResponse CAddConditionsView::OfferKeyEventL(const TKeyEvent &aKeyEvent, TEventCode aType)
{
    // Forward keys to the ListBox
    if(iListBox)
    {
        return iListBox->OfferKeyEventL(aKeyEvent, aType);
    }

    return EKeyWasNotConsumed;
}

// Return a control based on an index
CCoeControl *CAddConditionsView::ComponentControl(TInt aIndex) const
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
void CAddConditionsView::HandleListBoxEventL(CEikListBox *aListBox, TListBoxEvent aEvent)
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
                    case EListBoxItemDate:
                    {
                        // Date conditions
                        TUint16 year;
                        TUint8 month;
                        TUint8 day;
                        TUint8 used;

                        // Year
                        TInt value;
                        CAknNumberQueryDialog *dialog = CAknNumberQueryDialog::NewL(value);

                        if(dialog->ExecuteLD(R_APPLICATION_CUTCROSS_QUERY_CONDITION_YEAR))
                        {
                            year = value;
                            used |= BIT(KTIME_USED_YEAR_BIT);
                        }

                        // Month
                        dialog = CAknNumberQueryDialog::NewL(value);

                        if(dialog->ExecuteLD(R_APPLICATION_CUTCROSS_QUERY_CONDITION_MONTH))
                        {
                            month = value;
                            used |= BIT(KTIME_USED_MONTH_BIT);
                        }

                        // Day
                        dialog = CAknNumberQueryDialog::NewL(value);

                        if(dialog->ExecuteLD(R_APPLICATION_CUTCROSS_QUERY_CONDITION_DAY))
                        {
                            day = value;
                            used |= BIT(KTIME_USED_DAY_BIT);
                        }

                        // Set unsaved date data based on user input
                        CSaveConditionAction *saveConditionAction = CSaveConditionAction::GetInstanceL();
                        saveConditionAction->AddUnsavedConditionDateL(year, month, day, used);
                        break;
                    }
                    case EListBoxItemTime:
                    {
                        // Time conditions
                        TUint8 hour;
                        TUint8 minute;
                        TUint8 used;

                        // Hour
                        TInt value;
                        CAknNumberQueryDialog *dialog = CAknNumberQueryDialog::NewL(value);
    
                        if(dialog->ExecuteLD(R_APPLICATION_CUTCROSS_QUERY_CONDITION_HOUR))
                        {
                            hour = value;
                            used |= BIT(KTIME_USED_HOUR_BIT);
                        }
    
                        // Minute
                        dialog = CAknNumberQueryDialog::NewL(value);
    
                        if(dialog->ExecuteLD(R_APPLICATION_CUTCROSS_QUERY_CONDITION_MINUTE))
                        {
                            minute = value;
                            used |= BIT(KTIME_USED_MINUTE_BIT);
                        }

                        // Set unsaved time data
                        CSaveConditionAction *saveConditionAction = CSaveConditionAction::GetInstanceL();
                        saveConditionAction->AddUnsavedConditionTimeL(hour, minute, used);
                        break;
                    }
                }
            }
        }
    }
}

// Constructors
CAddConditionsView::CAddConditionsView()
{
}

CAddConditionsView *CAddConditionsView::NewL(const TRect &aRect)
{
    CAddConditionsView *self = CAddConditionsView::NewLC(aRect);
    CleanupStack::Pop(); // NewLC
    return self;
}

CAddConditionsView *CAddConditionsView::NewLC(const TRect &aRect)
{
    CAddConditionsView *self = new(ELeave) CAddConditionsView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self; // Will be popped off the cleanup stack by NewL
}

void CAddConditionsView::ConstructL(const TRect &aRect)
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
    listBoxItems->InsertL(EListBoxItemDate, _L("\tDate"));
    listBoxItems->InsertL(EListBoxItemTime, _L("\tTime"));
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
CAddConditionsView::~CAddConditionsView()
{
    if(iListBox)
    {
        delete iListBox;
    }
}
