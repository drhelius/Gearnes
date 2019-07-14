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
#include "common.h"
#include "mapper.h"
#include "G6502/g6502_memory_interface.h"

class Cartridge;

class Memory : public g6502::MemoryInterface
{
public:
    Memory(Cartridge* cartridge);
    virtual ~Memory();
    void Init();
    void Reset();
    void SetCurrentMapper(Mapper* mapper);
    Mapper* GetCurrentMapper();
    virtual u8 Read(u16 address);
    virtual void Write(u16 address, u8 value);
    virtual void Disassemble(u16 address, const char* disassembled_string);
    virtual bool IsDisassembled(u16 address);
    void MemoryDump(const char* file_path);

private:
    struct stDisassemble
    {
        char disassembled_string[32];
    };

private:
    Cartridge* cartridge_;
    u8* map_;
    Mapper* current_mapper_;
    stDisassemble* disassembled_map_;
};


inline u8 Memory::Read(u16 address)
{
    switch (address & 0xE000)
    {
        case 0x0000:
        {
            // 2KB internal RAM
            return map_[address & 0x07FF];
        }
        case 0x2000:
        {
            // NES PPU registers
            return map_[address & 0x0007];
        }
        case 0x4000:
        {
            switch (address)
            {
                case 0x4014:
                {
                    // OAM-DMA
                    return map_[address];
                }
                case 0x4016:
                {
                    // Joypad 1
                    return map_[address];
                }
                case 0x4017:
                {
                    // Joypad 2
                    return map_[address];
                }
                case 0x4009:
                case 0x400D:
                case 0x4018:
                case 0x4019:
                {
                    // Unused
                    Log("Reading unused IO register $%04X", address);
                    return map_[address];
                }
                default:
                {
                    if (address < 0x4020)
                    {
                        // APU
                        return map_[address];
                    }
                    else
                    {
                        // Expansion ROM
                        return current_mapper_->PerformRead(address);
                    }
                }
            }
        }
        case 0x6000:
        {
            // SRAM (WRAM)
            return current_mapper_->PerformRead(address);
        }
        default:
        {
            // PRG-ROM
            return current_mapper_->PerformRead(address);
        }
    }
}

inline void Memory::Write(u16 address, u8 value)
{
    switch (address & 0xE000)
    {
        case 0x0000:
        {
            // 2KB internal RAM
            map_[address & 0x07FF] = value;
            break;
        }
        case 0x2000:
        {
            // NES PPU registers
            map_[address & 0x0007] = value;
            break;
        }
        case 0x4000:
        {
            switch (address)
            {
                case 0x4014:
                {
                    // OAM-DMA
                    Log("Writing to OAM-DMA $%04X 0x%02X", address, value);
                    map_[address] = value;
                    break;
                }
                case 0x4016:
                {
                    // Joypad 1
                    map_[address] = value;
                    break;
                }
                case 0x4017:
                {
                    // Joypad 2
                    map_[address] = value;
                    break;
                }
                case 0x4009:
                case 0x400D:
                case 0x4018:
                case 0x4019:
                {
                    // Unused
                    Log("Writing to unused IO register $%04X 0x%02X", address, value);
                    map_[address] = value;
                    break;
                }
                default:
                {
                    if (address < 0x4020)
                    {
                        // APU
                        map_[address] = value;
                    }
                    else
                    {
                        // Expansion ROM
                        current_mapper_->PerformWrite(address, value);
                    }
                    break;
                }
            }
            break;
        }
        case 0x6000:
        {
            // SRAM (WRAM)
            current_mapper_->PerformWrite(address, value);
            break;
        }
        default:
        {
            // PRG-ROM
            current_mapper_->PerformWrite(address, value);
        }
    }
}

#endif	/* MEMORY_H */

