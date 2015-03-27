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

#ifndef MEMORY_H
#define	MEMORY_H

#include <vector>
#include "definitions.h"
#include "mapper.h"
#include "G6502/g6502_memory_interface.h"

class Memory : public g6502::MemoryInterface
{
public:
    Memory();
    virtual ~Memory();
    void Init();
    void Reset();
    void SetCurrentMapper(Mapper* mapper);
    Mapper* GetCurrentRule();
    virtual u8 Read(u16 address);
    virtual void Write(u16 address, u8 value);
    virtual u8 Retrieve(u16 address);
    virtual void Load(u16 address, u8 value);
    virtual void Disassemble(u16 address, const char* disassembled_string);
    virtual bool IsDisassembled(u16 address);
    void LoadSlotsFromROM(u8* rom, int size);
    void MemoryDump(const char* file_path);

private:

    struct stDisassemble
    {
        char disassembled_string[32];
    };

private:
    u8* map_;
    Mapper* current_mapper_;
    stDisassemble* disassembled_map_;
};

#include "memory_inline.h"

#endif	/* MEMORY_H */

