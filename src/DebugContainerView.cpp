// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

// [[[ begin generated region: do not modify [Generated System Includes]
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <Cutcross.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]

#include "Cutcross.hrh"
#include "DebugContainerView.h"
#include "CutcrossContainer.hrh"
#include "DebugContainer.h"
// ]]] end generated region [Generated User Includes]

#include "LocationHelper.h"

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CDebugContainerView::CDebugContainerView()
{
    // [[[ begin generated region: do not modify [Generated Contents]
    iDebugContainer = NULL;
    // ]]] end generated region [Generated Contents]

}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CDebugContainerView::~CDebugContainerView()
{
    // [[[ begin generated region: do not modify [Generated Contents]
    delete iDebugContainer;
    iDebugContainer = NULL;
    // ]]] end generated region [Generated Contents]

}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CDebugContainerView
 */
CDebugContainerView* CDebugContainerView::NewL()
{
    CDebugContainerView* self = CDebugContainerView::NewLC();
    CleanupStack::Pop(self);
    return self;
}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CDebugContainerView
 */
CDebugContainerView* CDebugContainerView::NewLC()
{
    CDebugContainerView* self = new (ELeave) CDebugContainerView();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}

/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */
void CDebugContainerView::ConstructL()
{
    // [[[ begin generated region: do not modify [Generated Code]
    BaseConstructL( R_DEBUG_CONTAINER_DEBUG_CONTAINER_VIEW);

    // ]]] end generated region [Generated Code]

AppUi()->
}

/**
 * @return The UID for this view
 */
TUid CDebugContainerView::Id() const
{
    return TUid::Uid(EDebugContainerViewId);
}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CDebugContainerView::HandleCommandL(TInt aCommand)
{
    // [[[ begin generated region: do not modify [Generated Code]
    TBool commandHandled = EFalse;
    switch(aCommand)
    { // code to dispatch to the AknView's menu and CBA commands is generated here
        default:
            break;
    }

    if(!commandHandled)
    {

        if(aCommand == EAknSoftkeyExit)
        {
            AppUi()->HandleCommandL(EEikCmdExit);
        }

    }
    // ]]] end generated region [Generated Code]

}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CDebugContainerView::DoActivateL(const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
{
    // [[[ begin generated region: do not modify [Generated Contents]
    SetupStatusPaneL();

    if(iDebugContainer == NULL)
    {
        iDebugContainer = CreateContainerL();
        iDebugContainer->SetMopParent(this);
        AppUi()->AddToStackL(*this, iDebugContainer);
    }
    // ]]] end generated region [Generated Contents]

}

/**
 */
void CDebugContainerView::DoDeactivate()
{
    // [[[ begin generated region: do not modify [Generated Contents]
    CleanupStatusPane();

    if(iDebugContainer != NULL)
    {
        AppUi()->RemoveFromViewStack(*this, iDebugContainer);
        delete iDebugContainer;
        iDebugContainer = NULL;
    }
    // ]]] end generated region [Generated Contents]

}

/** 
 * Handle status pane size change for this view (override)
 */
void CDebugContainerView::HandleStatusPaneSizeChange()
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
void CDebugContainerView::SetupStatusPaneL()
{
    // reset the context pane
    TUid contextPaneUid = TUid::Uid(EEikStatusPaneUidContext);
    CEikStatusPaneBase::TPaneCapabilities subPaneContext = StatusPane()->PaneCapabilities(contextPaneUid);
    if(subPaneContext.IsPresent() && subPaneContext.IsAppOwned())
    {
        CAknContextPane* context = static_cast<CAknContextPane*> (StatusPane()->ControlL(contextPaneUid));
        context->SetPictureToDefaultL();
    }

    // setup the title pane
    TUid titlePaneUid = TUid::Uid(EEikStatusPaneUidTitle);
    CEikStatusPaneBase::TPaneCapabilities subPaneTitle = StatusPane()->PaneCapabilities(titlePaneUid);
    if(subPaneTitle.IsPresent() && subPaneTitle.IsAppOwned())
    {
        CAknTitlePane* title = static_cast<CAknTitlePane*> (StatusPane()->ControlL(titlePaneUid));
        TResourceReader reader;
        iEikonEnv->CreateResourceReaderLC(reader, R_DEBUG_CONTAINER_TITLE_RESOURCE);
        title->SetFromResourceL(reader);
        CleanupStack::PopAndDestroy(); // reader internal state
    }

}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CDebugContainerView::CleanupStatusPane()
{
}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CDebugContainer::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CDebugContainer
 */
CDebugContainer* CDebugContainerView::CreateContainerL()
{
    return CDebugContainer::NewL(ClientRect(), NULL, this);
}

