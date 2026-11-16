// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef CUTCROSS_PAN_H
#define CUTCROSS_PAN_H

/** Cutcross application panic codes */
enum TCutcrossPanics
{
    ECutcrossUi = 1
// add further panics here
};

inline void Panic(TCutcrossPanics aReason)
{
    _LIT(applicationName, "Cutcross");
    User::Panic(applicationName, aReason);
}

#endif // CUTCROSS_PAN_H
