// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

// [[[ begin generated region: do not modify [Generated User Includes]
#include "client/CutcrossDocument.h"
#include "client/CutcrossAppUi.h"
// ]]] end generated region [Generated User Includes]

/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CCutcrossDocument::CCutcrossDocument(CEikApplication& anApplication) : CAknDocument(anApplication)
{
}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CCutcrossDocument::ConstructL()
{
}

/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CCutcrossDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CCutcrossDocument
 */
CCutcrossDocument* CCutcrossDocument::NewL( CEikApplication& aApp )
{
	CCutcrossDocument* self = new (ELeave)CCutcrossDocument(aApp);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CCutcrossDocument::CreateAppUiL()
{
	return new (ELeave)CCutcrossAppUi;
}
