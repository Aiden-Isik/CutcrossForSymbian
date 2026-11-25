// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <e32std.h>
#include <e32cmn.h>
#include <e32base.h>
#include <w32std.h>
#include <aknlists.h>
#include <coedef.h>
#include <coecntrl.h>
#include <aknmessagequerydialog.h> 

#include <avkon.hrh>

#include "View.h"
#include "MainView.h"
#include "AppUi.h"
#include "SaveConditionAction.h"
#include "Bit.h"
#include "ConditionActionData.h"

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

// Show condition-action information in a dialog
void CMainView::ShowConditionInformationL(TInt aIndex)
{
    CSaveConditionAction *saveConditionAction = CSaveConditionAction::GetInstanceL();
    struct Conditions *conditions = saveConditionAction->GetConditions();

    // Make sure conditions struct exists
    if(!conditions || !conditions->conditions)
    {
        User::Leave(KErrNotFound);
    }

    // Make sure index is within range
    if(aIndex >= conditions->count)
    {
        User::Leave(KErrArgument);
    }

    // Set header information
    _LIT(textBoxHeader, "Condition Information");
    TPtrC headerPointer(textBoxHeader);

    // Set body information
    // Conditions
    HBufC *conditionInformation = HBufC::NewL(sizeof("Conditions:\n"));
    CleanupStack::PushL(conditionInformation);
    conditionInformation->Des().Append(_L("Conditions:\n"));

    // Date/time condition
    if(conditions->conditions[aIndex].timeCondition)
    {
        TUint8 used = conditions->conditions[aIndex].timeCondition->used;
        TDateTime *dateTime = &(conditions->conditions[aIndex].timeCondition->time);

        if(BITFIELD_BIT(used, KTIME_USED_YEAR_BIT))
        {
            conditionInformation = conditionInformation->ReAllocL(conditionInformation->Length() + sizeof("Year: 65535\n")); // 65535 max
            CleanupStack::Pop(); // old conditionInformation
            CleanupStack::PushL(conditionInformation);
            conditionInformation->Des().AppendFormat(_L("Year: %d\n"), dateTime->Year());
        }

        if(BITFIELD_BIT(used, KTIME_USED_MONTH_BIT))
        {
            conditionInformation = conditionInformation->ReAllocL(conditionInformation->Length() + sizeof("Month: 12\n")); // 12 max
            CleanupStack::Pop(); // old conditionInformation
            CleanupStack::PushL(conditionInformation);
            conditionInformation->Des().AppendFormat(_L("Month: %d\n"), (TUint8)dateTime->Month() + 1); // 0-encoded
        }

        if(BITFIELD_BIT(used, KTIME_USED_DAY_BIT))
        {
            conditionInformation = conditionInformation->ReAllocL(conditionInformation->Length() + sizeof("Day: 31\n")); // 31 max
            CleanupStack::Pop(); // old conditionInformation
            CleanupStack::PushL(conditionInformation);
            conditionInformation->Des().AppendFormat(_L("Day: %d\n"), dateTime->Day() + 1); // 0-encoded
        }

        if(BITFIELD_BIT(used, KTIME_USED_HOUR_BIT))
        {
            conditionInformation = conditionInformation->ReAllocL(conditionInformation->Length() + sizeof("Hour: 23\n")); // 23 max
            CleanupStack::Pop(); // old conditionInformation
            CleanupStack::PushL(conditionInformation);
            conditionInformation->Des().AppendFormat(_L("Hour: %d\n"), dateTime->Hour());
        }

        if(BITFIELD_BIT(used, KTIME_USED_MINUTE_BIT))
        {
            conditionInformation = conditionInformation->ReAllocL(conditionInformation->Length() + sizeof("Minute: 59\n")); // 31 max
            CleanupStack::Pop(); // old conditionInformation
            CleanupStack::PushL(conditionInformation);
            conditionInformation->Des().AppendFormat(_L("Minute: %d\n"), dateTime->Minute());
        }
    }

    // Bluetooth device condition
    if(conditions->conditions[aIndex].bluetoothDeviceCondition)
    {
        conditionInformation = conditionInformation->ReAllocL(conditionInformation->Length() + sizeof("Bluetooth MAC: 000000000000\n"));
        CleanupStack::Pop(); // old conditionInformation
        CleanupStack::PushL(conditionInformation);
        conditionInformation->Des().AppendFormat(_L("Bluetooth MAC: %.12LX\n"), conditions->conditions[aIndex].bluetoothDeviceCondition->macAddress);
    }

    // Actions
    conditionInformation = conditionInformation->ReAllocL(conditionInformation->Length() + sizeof("\nActions:\n"));
    CleanupStack::Pop(); // old conditionInformation
    CleanupStack::PushL(conditionInformation);
    conditionInformation->Des().Append(_L("\nActions:\n"));

    // Vibration action
    if(conditions->conditions[aIndex].vibrationAction)
    {
        struct VibrationAction *vibration = conditions->conditions[aIndex].vibrationAction;
        conditionInformation = conditionInformation->ReAllocL(conditionInformation->Length() + sizeof("Vibration: 100% for 65535ms\n"));
        CleanupStack::Pop(); // old conditionInformation
        CleanupStack::PushL(conditionInformation);
        conditionInformation->Des().AppendFormat(_L("Vibration: %d%% for %dms\n"), vibration->intensity, vibration->duration);
    }

    // Display the dialog with all the information we have retrieved
    CAknMessageQueryDialog *dialog = CAknMessageQueryDialog::NewL(*conditionInformation);
    dialog->PrepareLC(R_AVKON_MESSAGE_QUERY_DIALOG);
    dialog->ButtonGroupContainer().MakeCommandVisible(EAknSoftkeyCancel, EFalse);
    dialog->QueryHeading()->SetTextL(headerPointer);
    dialog->RunLD();

    // Cleanup
    CleanupStack::PopAndDestroy(); // conditionInformation
}

// Handle list box item selections
void CMainView::HandleListBoxEventL(CEikListBox *aListBox, TListBoxEvent aEvent)
{
    switch(aEvent)
    {
        case EEventEnterKeyPressed:
        case EEventItemDoubleClicked:
        {
            if(iListBox)
            {
                // Show information on the currently selected condition-action set
                ShowConditionInformationL(iListBox->CurrentItemIndex());
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
