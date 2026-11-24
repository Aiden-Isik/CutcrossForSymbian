// SPDX-License-Identifier: AGPL-3.0-or-later
// Copyright (c) 2026 Aiden Isik

#ifndef BLUETOOTHCONTROLLER_H
#define BLUETOOTHCONTROLLER_H

#include <e32std.h>
#include <e32def.h>
#include <e32base.h>

class CBluetoothController: public CBase
{
    public:
        // Stand-in constructor
        static CBluetoothController *GetInstanceL();

        // Bluetooth MAC handling
        static void UpdateBluetoothMacsL();
        static RArray<TUint64> GetMacs();

    private:
        // The singleton object created from this class
        // Initialised to NULL as per C++ standard for static variables
        static CBluetoothController *iInstance;

        // Bluetooth MAC
        static RArray<TUint64> iMacAddresses;

        // Constructor
        CBluetoothController();
};

#endif // BLUETOOTHCONTROLLER_H
