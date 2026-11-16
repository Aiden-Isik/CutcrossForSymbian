// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

// [[[ begin generated region: do not modify [Generated System Includes]
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated Includes]
#include "client/CutcrossApplication.h"
#include "client/CutcrossDocument.h"
#ifdef EKA2
#include <eikstart.h>
#endif
// ]]] end generated region [Generated Includes]

/**
 * @brief Returns the application's UID (override from CApaApplication::AppDllUid())
 * @return UID for this application (KUidCutcrossApplication)
 */
TUid CCutcrossApplication::AppDllUid() const
{
	return KUidCutcrossApplication;
}

/**
 * @brief Creates the application's document (override from CApaApplication::CreateDocumentL())
 * @return Pointer to the created document object (CCutcrossDocument)
 */
CApaDocument* CCutcrossApplication::CreateDocumentL()
{
	return CCutcrossDocument::NewL(*this);
}

/**
 *	@brief Called by the application framework to construct the application object
 *  @return The application (CCutcrossApplication)
 */	
LOCAL_C CApaApplication* NewApplication()
{
	return new CCutcrossApplication;
}

/**
* @brief This standard export is the entry point for all Series 60 applications
* @return error code
 */	
GLDEF_C TInt E32Main()
{
	return EikStart::RunApplication(NewApplication);
}
