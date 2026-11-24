// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#include <e32std.h>
#include <e32def.h>
#include <e32base.h>
#include <es_sock.h>
#include <bt_sock.h>
#include <in_sock.h>

#include "BluetoothController.h"

CBluetoothController *CBluetoothController::iInstance = NULL;
RArray<TUint64> CBluetoothController::iMacAddresses;

// Update the list of bluetooth descriptors
void CBluetoothController::UpdateBluetoothMacsL()
{
    // Connect to the socket server
    RSocketServ socketServer;
    User::LeaveIfError(socketServer.Connect());
    CleanupClosePushL(socketServer);

    // Open resolver on the bluetooth link manager
    RHostResolver resolver;
    User::LeaveIfError(resolver.Open(socketServer, KBTAddrFamily, KBTLinkManager));
    CleanupClosePushL(resolver);

    // Configure bluetooth inquiry request
    TInquirySockAddr inquiryAddress;
    inquiryAddress.SetIAC(KGIAC);
    inquiryAddress.SetAction(KHostResInquiry | KHostResIgnoreCache);

    // Begin the inquiry and return the first result in nameEntry
    TNameEntry nameEntry;
    TRequestStatus status;
    resolver.GetByAddress(inquiryAddress, nameEntry, status);
    User::WaitForRequest(status);

    // Clear the old MAC addresses
    iMacAddresses.Reset();

    // Read every result
    while(status == KErrNone)
    {
        // Get the next bluetooth MAC address
        TBTDevAddr deviceAddress = ((TBTSockAddr&)nameEntry().iAddr).BTAddr();
        const TPtrC8 deviceAddressBytes = deviceAddress.Des();
        TUint64 tempAddress = 0;

        for(TUint8 i = 0; i < 6; i++)
        {
            tempAddress = (tempAddress << 8) | deviceAddressBytes[i];
        }

        iMacAddresses.AppendL(tempAddress);

        resolver.Next(nameEntry, status);
        User::WaitForRequest(status);
    }

    CleanupStack::PopAndDestroy(2); // resolver, socketServer
}

// Get all MAC addresses
RArray<TUint64> CBluetoothController::GetMacs()
{
    return iMacAddresses;
}

// Constructor
CBluetoothController::CBluetoothController()
{
}

// Stand-in constructor
// This should be called in place of the standard constructor, to enforce
// only one object for this class (singleton)
CBluetoothController *CBluetoothController::GetInstanceL()
{
    if(iInstance == NULL)
    {
        // NOTE: there is no need to deal with the cleanup stack here,
        // as this is a static method.
        iInstance = new(ELeave) CBluetoothController();
    }

    return iInstance;
}
