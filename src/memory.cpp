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

#include <iostream>
#include <iomanip>
#include <fstream>
#include "memory.h"
#include "cartridge.h"

/// MUST INLINE --->>>
///

u8 Memory::Read(u16 address)
{
    if (address < 0x2000)
    {
        // 2KB internal RAM
        address &= 0x07FF;
    }
    else if (address < 0x4000)
    {
        // NES PPU registers
        address &= 0x0007;
    }
    else if (address < 0x4020)
    {

        // NES APU and I/O registers
    }
    else
    {
        address &= 0x3FFF;
        return cartridge_->GetPRGROM()[address];
        // Cartridge space
    }
return 0;
    //current_mapper_->PerformRead(address);
}

void Memory::Write(u16 address, u8 value)
{
    //current_mapper_->PerformWrite(address, value);

    if (address < 0x2000)
    {
        // 2KB internal RAM
        address &= 0x07FF;
    }
    else if (address < 0x4000)
    {
        // NES PPU registers
        address &= 0x0007;
    }
    else if (address < 0x4020)
    {
        // NES APU and I/O registers
    }
    else
    {
        // Cartridge space
        //cartridge_->GetCHRROM()[0]=0;
    }
}

u8 Memory::Retrieve(u16 address)
{
    return 0;//map_[address];
}

void Memory::Load(u16 address, u8 value)
{
    //map_[address] = value;
}

///
/// MUST INLINE <<<---

Memory::Memory(Cartridge *cartridge)
{
    cartridge_ = cartridge;
    InitPointer(map_);
    InitPointer(current_mapper_);
    InitPointer(disassembled_map_);
}

Memory::~Memory()
{
    SafeDeleteArray(map_);
    SafeDeleteArray(current_mapper_);
    SafeDeleteArray(disassembled_map_);
}

void Memory::Init()
{
    Reset();
}

void Memory::Reset()
{

}

void Memory::SetCurrentMapper(Mapper* mapper)
{
    current_mapper_ = mapper;
}

Mapper* Memory::GetCurrentMapper()
{
    return current_mapper_;
}

void Memory::Disassemble(u16 address, const char* disassembled_string)
{
    //strcpy(disassembled_map_[address].disassembled_string, disassembled_string);
}

bool Memory::IsDisassembled(u16 address)
{
    return true;//disassembled_map_[address].disassembled_string[0] != 0;
}

void Memory::MemoryDump(const char* file_path)
{
    using namespace std;

    ofstream myfile(file_path, ios::out | ios::trunc);

    if (myfile.is_open())
    {


        myfile.close();
    }
}
