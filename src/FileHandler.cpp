// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#include <limits.h>

#include <e32err.h>
#include <e32cmn.h>
#include <f32file.h>

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
#define KCONDITION_ACTION_FILE_MAGIC 0xC07C7055

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
#define KCONDITION_USED_TIME_BIT 0

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

// Condition-action file format action data, version 0
//
// 0x0 - 0x2: Vibration intensity
// 0x2 - 0x3: Vibration duration
// 0x3 - 0x4: Bitfield specifying which actions are set
#define KACTION_USED_VIBRATE_BIT 0

struct __attribute__((packed)) ConditionsFileActionVibrateV0
{
        TUint16 duration;
        TInt8 intensity;
};

struct __attribute__((packed)) ConditionsFileActionDataV0
{
        struct ConditionsFileActionVibrateV0 vibrate;
        TUint8 actionsSet;
};

// Condition-action file format condition-action data, version 0
//
// 0x0+: Condition data
// 0x0+: Action data
struct __attribute__((packed)) ConditionsFileConditionActionV0
{
        struct ConditionsFileConditionDataV0 conditionData;
        struct ConditionsFileActionDataV0 actionData;
};

CFileHandler *CFileHandler::iInstance = NULL;

struct Conditions *CFileHandler::LoadConditionData()
{
    
}

// Convert condition data to condition-action file format
// and write it to a file.
void CFileHandler::SaveConditionData(const struct Conditions *aConditions, const TDesC &aFilename)
{
    // Populate the header
    struct ConditionsFileHeaderV0 header;
    header.magicAndVersion.magic = KCONDITION_ACTION_FILE_MAGIC;
    header.magicAndVersion.version = 0;
    header.conditionActionCount = aConditions->count;

    // Populate the condition-action data
    struct ConditionsFileConditionActionV0 *conditionActionData =
        new(ELeave) struct ConditionsFileConditionActionV0[header.conditionActionCount];
    CleanupStack::PushL(conditionActionData);

    memset(conditionActionData, 0, header.conditionActionCount * sizeof(struct ConditionsFileConditionActionV0));

    for(TUint16 i = 0; i < header.conditionActionCount; i++)
    {
        // If the time condition exists, translate it and store it here
        if(aConditions->conditions[i].timeCondition)
        {
            // Get pointers to time values to make the code a bit easier to read
            // This comes at the expense of a few bytes of memory, but this only
            // runs when explicitly triggered by the user anyways, and it isn't very much.
            struct ConditionsFileConditionTimeV0 *fileTime = &(conditionActionData[i].conditionData.time);
            TDateTime *runningTime = &(aConditions->conditions[i].timeCondition->time);

            // Set the time condition bitfield flag
            conditionActionData[i].conditionData.conditionsSet |= BIT(KCONDITION_USED_TIME_BIT);

            // Ensure year field is sane (TDateTime setters explicitly don't validate it)
            if(runningTime->Year() < 0 || runningTime->Year() > USHRT_MAX)
            {
                // Year isn't sane, abort
                User::Leave(KErrArgument);
            }

            // Set the time fields
            conditionActionData[i].conditionData.time.used = aConditions->conditions[i].timeCondition->used;
            fileTime->year = (TUint16)runningTime->Year();
            fileTime->month = (TUint8)runningTime->Month();
            fileTime->day = (TUint8)runningTime->Day();
            fileTime->hour = (TUint8)runningTime->Hour();
            fileTime->minute = (TUint8)runningTime->Minute();
        }

        // If the vibration action exists, translate it and store it here
        if(aConditions->conditions[i].vibrationAction)
        {
            struct ConditionsFileActionVibrateV0 *fileVibrate = &(conditionActionData[i].actionData.vibrate);
            struct VibrationAction *runningVibrate = aConditions->conditions[i].vibrationAction;
            
            // Set vibration action bitfield flag
            conditionActionData[i].actionData.actionsSet |= BIT(KACTION_USED_VIBRATE_BIT);

            // Make sure vibration intensity is valid (between -100% and 100%)
            if(runningVibrate->intensity < -100 || runningVibrate->intensity > 100)
            {
                // Vibration intensity is invalid, abort
                User::Leave(KErrArgument);
            }

            // Set vibration data in file data
            fileVibrate->duration = runningVibrate->duration;
            fileVibrate->intensity = runningVibrate->intensity;
        }
    }

    // Open connection to the file server
    RFs fileServer;
    User::LeaveIfError(fileServer.Connect());
    CleanupClosePushL(fileServer);

    // Create condition-action file
    RFile file;
    User::LeaveIfError(file.Replace(fileServer, aFilename, EFileWrite | EFileShareExclusive));
    CleanupClosePushL(file);

    // Write the header to the file
    TPtrC8 *headerDescriptor = new(ELeave) TPtrC8((const TUint8*)&header, sizeof(struct ConditionsFileHeaderV0));
    CleanupStack::PushL(headerDescriptor);
    User::LeaveIfError(file.Write(*headerDescriptor));
    CleanupStack::PopAndDestroy(); // headerDescriptor

    // Write the condition-action data to the file
    TPtrC8 *dataDescriptor =
        new(ELeave) TPtrC8((const TUint8*)conditionActionData,
                           sizeof(struct ConditionsFileConditionActionV0) * header.conditionActionCount);
    CleanupStack::PushL(dataDescriptor);
    User::LeaveIfError(file.Write(sizeof(ConditionsFileHeaderV0), *dataDescriptor));

    // Cleanup
    CleanupStack::PopAndDestroy(4); // dataDescriptor, file, fileServer, conditionActionData
    return;
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
