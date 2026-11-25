// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <e32base.h>
#include <e32def.h>
#include <e32err.h>
#include <http.h>

#include "HttpHandler.h"

void CHttpHandler::MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent &aEvent)
{
    switch(aEvent.iStatus)
    {
        case THTTPEvent::EGotResponseBodyData:
        {
            // Store the status code
            iHttpStatusCode = aTransaction.Response().StatusCode();

            // If we got data back in the body, add it to the stored response
            TPtrC8 bodyData;
            aTransaction.Response().Body()->GetNextDataPart(bodyData);
            iHttpResponseBody.ReAllocL(iHttpResponseBody.Length() + bodyData.Length());
            iHttpResponseBody.Append(bodyData);

            // Done, release the data
            aTransaction.Response().Body()->ReleaseData();
            break;
        }
        case THTTPEvent::ESucceeded:
        case THTTPEvent::EFailed:
        {
            aTransaction.Close();
            CActiveScheduler::Stop();
            break;
        }
        default:
        {
            break;
        }
    }
}

TInt CHttpHandler::MHFRunError(TInt, RHTTPTransaction aTransaction, const THTTPEvent &aEvent)
{
    // No error
    return KErrNone;
}
