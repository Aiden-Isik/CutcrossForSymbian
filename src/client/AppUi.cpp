// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <aknappui.h>
#include <aknmessagequerydialog.h>
#include <eikappui.h>
#include <eikmenup.h>
#include <e32def.h>
#include <e32std.h>
#include <e32err.h>

#include <avkon.hrh>

#include "AppUi.h"
#include "MainView.h"
#include "AddView.h"
#include "AddConditionsView.h"
#include "AddActionsView.h"
#include "Version.h"
#include "ConditionActionData.h"
#include "SaveConditionAction.h"

#include "Cutcross.rsg"

// Macros to convert macros which expand to non-string to string
#define STR_HELPER(macro) #macro
#define STR(macro) STR_HELPER(macro)

// Switch the current view
void CAppUi::SwitchViewL(TUint8 id)
{
    // Delete the current view
    if(iView)
    {
        RemoveFromStack(iView);

        if(iPreviousView)
        {
            delete iPreviousView;
            iPreviousView = iView;
            iView = NULL;
        }
    }

    // Create view object corresponding to the ID
    switch(id)
    {
        case EPageMainId:
        {
            iView = CMainView::NewL(ClientRect());
            break;
        }
        case EPageAddId:
        {
            iView = CAddView::NewL(ClientRect());
            break;
        }
        case EPageAddConditionsId:
        {
            iView = CAddConditionsView::NewL(ClientRect());
            break;
        }
        case EPageAddActionsId:
        {
            iView = CAddActionsView::NewL(ClientRect());
            break;
        }
        default:
        {
            User::Leave(KErrArgument);
            break; // Should never get here, but no harm in it
        }
    }

    iView->SetMopParent(this); // Owned by this object
    AddToStackL(iView);
    return;
}

// Show the "about" dialog
void CAppUi::ShowAboutDialogL()
{
    // Populate the text box
    _LIT(textBoxHeader, "About Cutcross");
    TPtrC headerPointer(textBoxHeader);

    _LIT(textBoxText, "Cutcross for Symbian S60v3+\n\n"

                      "Version " KCUTCROSS_VERSION "\n\n"

                      "Built with GCC " STR(__GNUC__) "." STR(__GNUC_MINOR__) "." STR(__GNUC_PATCHLEVEL__) "\n\n"

                      "Copyright (c) 2026 Aiden Isik\n"
                      "<aidenisik@member.fsf.org>\n\n"

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
    TPtrC textPointer(textBoxText);

    CAknMessageQueryDialog *dialog = CAknMessageQueryDialog::NewL(textPointer);
    dialog->PrepareLC(R_AVKON_MESSAGE_QUERY_DIALOG);
    dialog->ButtonGroupContainer().MakeCommandVisible(EAknSoftkeyCancel, EFalse);
    dialog->QueryHeading()->SetTextL(headerPointer);
    dialog->RunLD();
}

// Handle commands from the application framework
void CAppUi::HandleCommandL(TInt aCommand)
{
    switch(aCommand)
    {
        case EAknSoftkeyExit:
        case EEikCmdExit:
        {
            Exit();
            break; // We should never get here, but if we do handle it gracefully
        }
        case ESwitchPageMain:
        {
            // Switch the current view to the main menu page
            SwitchViewL(EPageMainId);
            break;
        }
        case ESwitchPageAbout:
        {
            // Switch the current view to the about page
            ShowAboutDialogL();
            break;
        }
        case ESwitchPageAdd:
        {
            SwitchViewL(EPageAddId);
            break;
        }
        case ESwitchPageAddConditions:
        {
            SwitchViewL(EPageAddConditionsId);
            break;
        }
        case ESwitchPageAddActions:
        {
            SwitchViewL(EPageAddActionsId);
            break;
        }
        case EAddSave:
        {
            // Save the unsaved condition-action data set in the add menu,
            // then save the result to file
            CSaveConditionAction *saveConditionAction = CSaveConditionAction::GetInstanceL();
            saveConditionAction->AddConditionFromUnsavedL();
            saveConditionAction->SaveConditionsToFileL();
            break;
        }
        default:
        {
            // We don't have a handler for this command, send it up the chain
            CAknAppUi::HandleCommandL(aCommand);
            break;
        }
    }
}

// Populate options menu based on the current view
void CAppUi::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane *aMenuPane)
{
    if(aResourceId == R_APPLICATION_CUTCROSS_MENU)
    {
        CEikMenuPaneItem::SData newOption;

        switch(iView->GetId())
        {
            case EPageMainId:
            {
                // Add "add" menu item
                newOption.iCommandId = ESwitchPageAdd;
                newOption.iText = _L("Add");
                newOption.iCascadeId = 0;
                newOption.iFlags = 0;
                aMenuPane->AddMenuItemL(newOption);

                // Add "delete menu item"
                newOption.iCommandId = EMainDelete;
                newOption.iText = _L("Delete");
                newOption.iCascadeId = 0;
                newOption.iFlags = 0;
                aMenuPane->AddMenuItemL(newOption);
                break;
            }
            case EPageAddId:
            {
                // Add "save" menu item
                newOption.iCommandId = EAddSave;
                newOption.iText = _L("Save");
                newOption.iCascadeId = 0;
                newOption.iFlags = 0;
                aMenuPane->AddMenuItemL(newOption);

                // Add "main menu" menu item
                newOption.iCommandId = ESwitchPageMain;
                newOption.iText = _L("Main menu");
                newOption.iCascadeId = 0;
                newOption.iFlags = 0;
                aMenuPane->AddMenuItemL(newOption);
                break;
            }
            case EPageAddConditionsId:
            {
                // Add "back" menu item
                newOption.iCommandId = ESwitchPageAdd;
                newOption.iText = _L("Back");
                newOption.iCascadeId = 0;
                newOption.iFlags = 0;
                aMenuPane->AddMenuItemL(newOption);
                break;
            }
            case EPageAddActionsId:
            {
                // Add "back" menu item
                newOption.iCommandId = ESwitchPageAdd;
                newOption.iText = _L("Back");
                newOption.iCascadeId = 0;
                newOption.iFlags = 0;
                aMenuPane->AddMenuItemL(newOption);
                break;
            }
        }

        // Add "about" menu item to the main options menu
        newOption.iCommandId = ESwitchPageAbout;
        newOption.iText = _L("About");
        newOption.iCascadeId = 0;
        newOption.iFlags = 0;
        aMenuPane->AddMenuItemL(newOption);

        // Add "exit" menu item
        newOption.iCommandId = EEikCmdExit;
        newOption.iText = _L("Exit");
        newOption.iCascadeId = 0;
        newOption.iFlags = 0;
        aMenuPane->AddMenuItemL(newOption);
    }

    CAknAppUi::DynInitMenuPaneL(aResourceId, aMenuPane);
}

// Constructors
CAppUi::CAppUi()
{
}

void CAppUi::ConstructL()
{
    // Initialise base UI with theme support, which is a requirement
    // for S60v2 FP3 and later, for certain controls to render properly.
    BaseConstructL(EAknEnableSkin);

    // Create default view object
    iView = CMainView::NewL(ClientRect());
    iView->SetMopParent(this); // Owned by this object
    AddToStackL(iView);
    iPreviousView = NULL;

    // Initialise condition-action data
    CSaveConditionAction *saveConditionAction = CSaveConditionAction::GetInstanceL();
    saveConditionAction->InitialiseConditionsL();
    saveConditionAction->InitialiseUnsavedL();
}

// Destructor
CAppUi::~CAppUi()
{
    if(iView)
    {
        // Delete active view
        RemoveFromStack(iView);
        delete iView;
    }
}
