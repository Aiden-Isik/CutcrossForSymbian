// Copyright (c) 2026 Aiden Isik
// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef BIT_H_
#define BIT_H_

// Bitfield manipulation macros
#define BIT(bit) (1 << (bit))
#define BITFIELD_BIT(field, bit) (((field) >> (bit)) & 1)

#endif /* BIT_H_ */
