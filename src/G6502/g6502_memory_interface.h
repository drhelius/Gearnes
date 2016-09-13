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

#ifndef G6502_MEMORYINTERFACE_H_
#define	G6502_MEMORYINTERFACE_H_

#include "g6502_definitions.h"

namespace g6502
{
    
class MemoryInterface
{
public:
    MemoryInterface() {}
    virtual ~MemoryInterface() {}
    virtual u8 Read(u16 address) = 0;
    virtual void Write(u16 address, u8 value) = 0;
    virtual void Disassemble(u16 address, const char* disassembled_string) = 0;
    virtual bool IsDisassembled(u16 address) = 0;
};

} // namespace g6502

#endif // G6502_MEMORYINTERFACE_H_

