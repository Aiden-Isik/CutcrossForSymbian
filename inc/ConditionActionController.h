// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef CONDITIONACTIONCONTROLLER_H
#define CONDITIONACTIONCONTROLLER_H

#include <e32std.h>
#include <e32base.h>

// Bitfield manipulation macros
#define BIT(bit) (1 << bit)
#define BITFIELD_BIT(field, bit) ((field >> bit) & 1)

struct VibrationAction
{
        TUint16 duration;
        TInt8 intensity;
};

// Time condition bitfield definitions
#define TIME_USED_MICROSECOND_BIT 0
#define TIME_USED_SECOND_BIT 1
#define TIME_USED_MINUTE_BIT 2
#define TIME_USED_HOUR_BIT 3
#define TIME_USED_DAY_BIT 4
#define TIME_USED_MONTH_BIT 5
#define TIME_USED_YEAR_BIT 6

// Struct for a simple time condition
//
// Contains the time at which the condition is met,
// along with a bitfield specifying which components are actually used.
struct TimeCondition
{
        TDateTime time;
        TUint8 used; // Bitfield
};

// Struct for a single set of conditions
//
// It contains pointers to and counts of whichever condition types are used.
// This is to save memory, in the event that a given condition type is not
// actually used. Instead of taking up the whole size of every condition type's
// struct, it will only take up 32 bits per valid condition type if it is not used.
//
// It also contains a boolean specifying whether or not the current met conditions
// have already caused the actions to fire, in order to prevent duplicate firing.
//
// It also contains information on which actions to fire.
struct Condition
{
        struct TimeCondition *timeCondition;
        struct VibrationAction *vibrationAction;
        TBool hasFired;
};

// Struct for the array of all sets of conditions
struct Conditions
{
        struct Condition *conditions;
        TUint16 count;
};

class CConditionActionController: public CBase
{
    public:
        // Stand-in constructor
        static CConditionActionController *GetInstanceL();

        // Main condition-action loop, the heart of the application
        void RunLoopL();

    private:
        // The singleton object created from this class
        // Initialised to NULL as per C++ standard for static variables
        static CConditionActionController *iInstance;

        // The main conditions struct, holding all conditions and associated actions
        struct Conditions iConditions;

        // Constructor
        CConditionActionController();
};

#endif // CONDITIONACTIONCONTROLLER_H
