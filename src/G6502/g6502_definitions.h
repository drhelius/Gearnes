/*
 * G6502 - 6502 Emulator
 * Copyright (C) 2016  Ignacio Sanchez Gines

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

#ifndef G6502_DEFINITIONS_H_
#define	G6502_DEFINITIONS_H_

#include "g6502_types.h"

namespace g6502
{

#define G6502_DEBUG 1

#ifdef G6502_DEBUG
    #define G6502_DISASM 1
#endif
    
#define FLAG_CARRY 0x01
#define FLAG_ZERO 0x02
#define FLAG_IRQ 0x04
#define FLAG_DECIMAL 0x08
#define FLAG_BRK 0x10
#define FLAG_UNUSED 0x20
#define FLAG_OVERFLOW 0x40
#define FLAG_NEGATIVE 0x80



} // namespace g6502

#endif // G6502_DEFINITIONS_H_

