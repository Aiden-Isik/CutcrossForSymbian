// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

// [[[ begin generated region: do not modify [Generated System Includes]
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <akncontext.h>
#include <akntitle.h>
#include <stringloader.h>
#include <barsread.h>
#include <eikbtgpc.h>
#include <Cutcross.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]

#include "Cutcross.hrh"
#include "CutcrossContainerView.h"
#include "CutcrossContainer.hrh"
#include "CutcrossContainer.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CCutcrossContainerView::CCutcrossContainerView()
{
    // [[[ begin generated region: do not modify [Generated Contents]
	iCutcrossContainer = NULL;
    // ]]] end generated region [Generated Contents]
}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CCutcrossContainerView::~CCutcrossContainerView()
{
    // [[[ begin generated region: do not modify [Generated Contents]
	delete iCutcrossContainer;
	iCutcrossContainer = NULL;
    // ]]] end generated region [Generated Contents]
}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CCutcrossContainerView
 */
CCutcrossContainerView* CCutcrossContainerView::NewL()
{
    CCutcrossContainerView* self = CCutcrossContainerView::NewLC();
    CleanupStack::Pop(self);
    return self;
}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CCutcrossContainerView
 */
CCutcrossContainerView* CCutcrossContainerView::NewLC()
{
    CCutcrossContainerView* self = new (ELeave) CCutcrossContainerView();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}

/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */
void CCutcrossContainerView::ConstructL()
{
    // [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_CUTCROSS_CONTAINER_CUTCROSS_CONTAINER_VIEW );
				
    // ]]] end generated region [Generated Code]

    // add your own initialization code here
}

/**
 * @return The UID for this view
 */
TUid CCutcrossContainerView::Id() const
{
    return TUid::Uid(ECutcrossContainerViewId);
}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CCutcrossContainerView::HandleCommandL(TInt aCommand)
{
    // [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
		case ECutcrossContainerViewDebugging_InfoMenuItemCommand:
			commandHandled = HandleDebugging_InfoMenuItemSelectedL( aCommand );
			break;
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		if ( aCommand == EAknSoftkeyExit )
			{
			AppUi()->HandleCommandL( EEikCmdExit );
			}
	
		}
    // ]]] end generated region [Generated Code]
}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CCutcrossContainerView::DoActivateL(const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
{
    // [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iCutcrossContainer == NULL )
		{
		iCutcrossContainer = CreateContainerL();
		iCutcrossContainer->SetMopParent( this );
		AppUi()->AddToStackL( *this, iCutcrossContainer );
		} 
    // ]]] end generated region [Generated Contents]
}

/**
 */
void CCutcrossContainerView::DoDeactivate()
{
    // [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iCutcrossContainer != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iCutcrossContainer );
		delete iCutcrossContainer;
		iCutcrossContainer = NULL;
		}
    // ]]] end generated region [Generated Contents]
}

/** 
 * Handle status pane size change for this view (override)
 */
void CCutcrossContainerView::HandleStatusPaneSizeChange()
{
    CAknView::HandleStatusPaneSizeChange();

    // this may fail, but we're not able to propagate exceptions here
    TVwsViewId view;
    AppUi()->GetActiveViewId(view);
    if(view.iViewUid == Id())
    {
        TInt result;
        TRAP(result, SetupStatusPaneL());
    }

    // [[[ begin generated region: do not modify [Generated Code]
    // ]]] end generated region [Generated Code]
}

// [[[ begin generated function: do not modify
void CCutcrossContainerView::SetupStatusPaneL()
	{
	// reset the context pane
	TUid contextPaneUid = TUid::Uid( EEikStatusPaneUidContext );
	CEikStatusPaneBase::TPaneCapabilities subPaneContext = 
		StatusPane()->PaneCapabilities( contextPaneUid );
	if ( subPaneContext.IsPresent() && subPaneContext.IsAppOwned() )
		{
		CAknContextPane* context = static_cast< CAknContextPane* > ( 
			StatusPane()->ControlL( contextPaneUid ) );
		context->SetPictureToDefaultL();
		}
	
	// setup the title pane
	TUid titlePaneUid = TUid::Uid( EEikStatusPaneUidTitle );
	CEikStatusPaneBase::TPaneCapabilities subPaneTitle = 
		StatusPane()->PaneCapabilities( titlePaneUid );
	if ( subPaneTitle.IsPresent() && subPaneTitle.IsAppOwned() )
		{
		CAknTitlePane* title = static_cast< CAknTitlePane* >( 
			StatusPane()->ControlL( titlePaneUid ) );
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_CUTCROSS_CONTAINER_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CCutcrossContainerView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CCutcrossContainer::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CCutcrossContainer
 */
CCutcrossContainer* CCutcrossContainerView::CreateContainerL()
{
    return CCutcrossContainer::NewL(ClientRect(), NULL, this);
}

/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CCutcrossContainerView::HandleDebugging_InfoMenuItemSelectedL(TInt aCommand)
{
    AppUi()->ActivateLocalViewL(TUid::Uid(EDebugContainerViewId));
    return ETrue;
}

