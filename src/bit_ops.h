/*
 * Gearnes - NES / Famicom Emulator
 * Copyright (C) 2015  Ignacio Sanchez Gines

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/
 *
 */

#ifndef BITOPS_H_
#define	BITOPS_H_

#include "G6502/g6502_types.h"

namespace Gearnes
{

inline u8 SetBit(const u8 value, const u8 bit)
{
    return value | static_cast<u8>(0x01 << bit);
}

inline u8 UnsetBit(const u8 value, const u8 bit)
{
    return value & (~(0x01 << bit));
}

inline bool IsSetBit(const u8 value, const u8 bit)
{
    return (value & (0x01 << bit)) != 0;
}

inline u8 FlipBit(const u8 value, const u8 bit)
{
    return value ^ static_cast<u8>(0x01 << bit);
}

} // namespace Gearnes

#endif // BITOPS_H_

