// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

// [[[ begin generated region: do not modify [Generated System Includes]
#include <eikmenub.h>
#include <akncontext.h>
#include <akntitle.h>
#include <Cutcross.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "CutcrossAppUi.h"
#include "Cutcross.hrh"
#include "CutcrossContainer.hrh"
#include "CutcrossContainerView.h"
#include "DebugContainerView.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * Construct the CCutcrossAppUi instance
 */ 
CCutcrossAppUi::CCutcrossAppUi()
{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]	
}

/** 
 * The appui's destructor removes the container from the control
 * stack and destroys it.
 */
CCutcrossAppUi::~CCutcrossAppUi()
{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
}

// [[[ begin generated function: do not modify
void CCutcrossAppUi::InitializeContainersL()
	{
	iCutcrossContainerView = CCutcrossContainerView::NewL();
	AddViewL( iCutcrossContainerView );
	SetDefaultViewL( *iCutcrossContainerView );
	iDebugContainerView = CDebugContainerView::NewL();
	AddViewL( iDebugContainerView );
	}
// ]]] end generated function

/**
 * Handle a command for this appui (override)
 * @param aCommand command id to be handled
 */
void CCutcrossAppUi::HandleCommandL(TInt aCommand)
{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{ // code to dispatch to the AppUi's menu and CBA commands is generated here
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
		if ( aCommand == EAknSoftkeyExit || aCommand == EEikCmdExit )
			{
			Exit();
			}
		}
	// ]]] end generated region [Generated Code]
}

/** 
 * Override of the HandleResourceChangeL virtual function
 */
void CCutcrossAppUi::HandleResourceChangeL(TInt aType)
{
	CAknViewAppUi::HandleResourceChangeL(aType);
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
}
				
/** 
 * Override of the HandleKeyEventL virtual function
 * @return EKeyWasConsumed if event was handled, EKeyWasNotConsumed if not
 * @param aKeyEvent 
 * @param aType 
 */
TKeyResponse CCutcrossAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,
											 TEventCode aType)
{
	// The inherited HandleKeyEventL is private and cannot be called
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	return EKeyWasNotConsumed;
}

/** 
 * Override of the HandleViewDeactivation virtual function
 *
 * @param aViewIdToBeDeactivated 
 * @param aNewlyActivatedViewId 
 */
void CCutcrossAppUi::HandleViewDeactivation(const TVwsViewId& aViewIdToBeDeactivated,
											const TVwsViewId& aNewlyActivatedViewId)
{
	CAknViewAppUi::HandleViewDeactivation(aViewIdToBeDeactivated,
										  aNewlyActivatedViewId);
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here. 
 */ 
void CCutcrossAppUi::ConstructL()
{
	// [[[ begin generated region: do not modify [Generated Contents]
	
	BaseConstructL( EAknEnableSkin ); 
	InitializeContainersL();
	// ]]] end generated region [Generated Contents]
	
}
