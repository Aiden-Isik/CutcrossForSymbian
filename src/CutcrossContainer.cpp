// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

// [[[ begin generated region: do not modify [Generated System Includes]
#include <aknviewappui.h>
#include <eikappui.h>
#include <Cutcross.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "CutcrossContainer.h"
#include "CutcrossContainerView.h"
#include "Cutcross.hrh"
#include "CutcrossContainer.hrh"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not 
 * contain any code that could leave.
 */
CCutcrossContainer::CCutcrossContainer()
{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
}

/** 
 * Destroy child controls.
 */
CCutcrossContainer::~CCutcrossContainer()
{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
}
				
/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is not left on cleanup stack.
 * @param aRect bounding rectangle
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return initialized instance of CCutcrossContainer
 */
CCutcrossContainer* CCutcrossContainer::NewL(const TRect& aRect, const CCoeControl* aParent,
											 MEikCommandObserver* aCommandObserver)
{
	CCutcrossContainer* self = CCutcrossContainer::NewLC(aRect, aParent, aCommandObserver);
	CleanupStack::Pop(self);
	return self;
}

/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is left on cleanup stack.
 * @param aRect The rectangle for this window
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return new instance of CCutcrossContainer
 */
CCutcrossContainer* CCutcrossContainer::NewLC(const TRect& aRect, const CCoeControl* aParent,
											  MEikCommandObserver* aCommandObserver)
{
	CCutcrossContainer* self = new (ELeave)CCutcrossContainer();
	CleanupStack::PushL(self);
	self->ConstructL(aRect, aParent, aCommandObserver);
	return self;
}
			
/**
 * Construct the control (second phase).
 *  Creates a window to contain the controls and activates it.
 * @param aRect bounding rectangle
 * @param aCommandObserver command observer
 * @param aParent owning parent, or NULL
 */ 
void CCutcrossContainer::ConstructL(const TRect& aRect, const CCoeControl* aParent,
									MEikCommandObserver* aCommandObserver)
{
	if(aParent == NULL)
	{
		CreateWindowL();
	}
	else
	{
		SetContainerWindowL(*aParent);
	}

	iFocusControl = NULL;
	iCommandObserver = aCommandObserver;
	InitializeControlsL();
	SetRect(aRect);
	ActivateL();
	// [[[ begin generated region: do not modify [Post-ActivateL initializations]
	// ]]] end generated region [Post-ActivateL initializations]
}
			
/**
* Return the number of controls in the container (override)
* @return count
*/
TInt CCutcrossContainer::CountComponentControls() const
{
	return ( int ) ELastControl;
}
				
/**
* Get the control with the given index (override)
* @param aIndex Control index [0...n) (limited by #CountComponentControls)
* @return Pointer to control
*/
CCoeControl* CCutcrossContainer::ComponentControl( TInt aIndex ) const
{
	// [[[ begin generated region: do not modify [Generated Contents]
	switch ( aIndex )
		{
		}
	// ]]] end generated region [Generated Contents]

	// handle any user controls here...
	return NULL;
	}
				
/**
 *	Handle resizing of the container. This implementation will lay out
 *  full-sized controls like list boxes for any screen size, and will layout
 *  labels, editors, etc. to the size they were given in the UI designer.
 *  This code will need to be modified to adjust arbitrary controls to
 *  any screen size.
 */				
void CCutcrossContainer::SizeChanged()
{
	CCoeControl::SizeChanged();
	LayoutControls();
	// [[[ begin generated region: do not modify [Generated Contents]
			
	// ]]] end generated region [Generated Contents]
}

// [[[ begin generated function: do not modify
/**
 * Layout components as specified in the UI Designer
 */
void CCutcrossContainer::LayoutControls()
	{
	}
// ]]] end generated function

/**
 *	Handle key events.
 */				
TKeyResponse CCutcrossContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
{
	// [[[ begin generated region: do not modify [Generated Contents]
	
	// ]]] end generated region [Generated Contents]
	
	if(iFocusControl != NULL && iFocusControl->OfferKeyEventL(aKeyEvent, aType) == EKeyWasConsumed)
	{
		return EKeyWasConsumed;
	}

	return CCoeControl::OfferKeyEventL( aKeyEvent, aType );
}
				
// [[[ begin generated function: do not modify
/**
 *	Initialize each control upon creation.
 */				
void CCutcrossContainer::InitializeControlsL()
{
	
}
// ]]] end generated function

/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CCutcrossContainer::HandleResourceChange( TInt aType )
{
	CCoeControl::HandleResourceChange(aType);
	SetRect(iAvkonViewAppUi->View(TUid::Uid(ECutcrossContainerViewId))->ClientRect());
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
}

/**
 *	Draw container contents.
 */				
void CCutcrossContainer::Draw( const TRect& aRect ) const
{
	// [[[ begin generated region: do not modify [Generated Contents]
	CWindowGc& gc = SystemGc();
	gc.Clear( aRect );
	
	// ]]] end generated region [Generated Contents]
}
