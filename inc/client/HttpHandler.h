// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef HTTPHANDLER_H_
#define HTTPHANDLER_H_

#include <e32base.h>
#include <e32def.h>
#include <http.h>

class CHttpHandler: public CBase, public MHTTPTransactionCallback
{
    public:
        // Handle HTTP requests
        void MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent &aEvent);
        TInt MHFRunError(TInt, RHTTPTransaction aTransaction, const THTTPEvent &aEvent);

        TInt iHttpStatusCode;
        RBuf8 iHttpResponseBody;
};

#endif /* HTTPHANDLER_H_ */
