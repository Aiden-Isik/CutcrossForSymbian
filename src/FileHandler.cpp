// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include "FileHandler.h"

// Condition-action file format structs
//
// Structs are packed so the compiler used doesn't influence whether the file
// is able to be read correctly.
//
// To preserve alignment where possible for performance reasons, some members
// may be ordered in a slightly odd way.

// The magic and version header. This will always be the same format for
// backwards compatibility.
struct __attribute__((packed)) ConditionsFileMagicAndVersion
{
        TUint32 magic; // Must always be 0xC07C7055
        TUint16 version;
};

// Condition-action file format header, version 0
// WARNING: Version 0 is in development and subject to change
//
// 0x0 - 0x4: magic (0xC07C7055)
// 0x4 - 0x6: version (0x0000)
// 0x6 - 0x8: conditionActionCount
// 0x8+:      condition-action structs * conditionActionCount
struct __attribute__((packed)) ConditionsFileHeaderV0
{
        struct ConditionsFileMagicAndVersion magicAndVersion;
        TUint16 conditionActionCount;
};

// Condition-action file format condition data, version 0
//
// 0x0 - 0x2: Year
// 0x2 - 0x3: Month
// 0x3 - 0x4: Day
// 0x4 - 0x5: Hour
// 0x5 - 0x6: Minute
// 0x6 - 0x7: Bitfield specifying which time fields are used
// 0x7 - 0x8: Bitfield specifying which conditions are set
#define CONDITION_USED_TIME_BIT 0

struct __attribute__((packed)) ConditionsFileConditionTimeV0
{
        TUint16 year;
        TUint8 month;
        TUint8 day;
        TUint8 hour;
        TUint8 minute;
        TUint8 used;
};

struct __attribute__((packed)) ConditionsFileConditionDataV0
{
        struct ConditionsFileConditionTimeV0 time;
        TUint8 conditionsSet;
};

// Condition-action file format condition-action data, version 0
//
// 0x0+: Condition data
// 0x0+: Action data
// Condition-action file format action data, version 0
//
// 0x0 - 0x2: Vibration intensity
// 0x2 - 0x3: Vibration duration
// 0x3 - 0x4: Bitfield specifying which actions are set
#define ACTION_USED_VIBRATE_BIT 0

struct __attribute__((packed)) ConditionsFileActionVibrateV0
{
        TUint16 duration;
        TInt8 intensity;
};

struct __attribute__((packed)) ConditionsFileActionDataV0
{
        struct ConditionsFileActionVibrateV0;
        TUint8 actionsSet;
};

struct __attribute__((packed)) ConditionsFileConditionActionV0
{
        struct ConditionsFileConditionDataV0 conditionData;
        struct ConditionsFileActionDataV0 actionData;
};

CFileHandler *CFileHandler::iInstance = NULL;

struct Conditions *CFileHandler::LoadConditionData()
{

}

void CFileHandler::SaveConditionData()
{

}

CFileHandler::CFileHandler()
{
}

// Stand-in constructor
// This should be called in place of the standard constructor, to enforce
// only one object for this class (singleton)
CFileHandler *CFileHandler::GetInstanceL()
{
    if(iInstance == NULL)
    {
        // NOTE: there is no need to deal with the cleanup stack here,
        // as this is a static method.
        iInstance = new(ELeave) CFileHandler();
    }
    
    return iInstance;
}
