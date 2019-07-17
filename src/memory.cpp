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
#include <cstring>
#include "memory.h"

namespace Gearnes
{

Memory::Memory(Video* video)
{
    video_ = video;
    InitPointer(map_);
    InitPointer(current_mapper_);
    InitPointer(disassembled_map_);

    map_ = new u8[0x10000];
}

Memory::~Memory()
{
    SafeDeleteArray(map_);
    SafeDeleteArray(disassembled_map_);
}

void Memory::Init()
{
    Reset();
}

void Memory::Reset()
{
    memset(map_, 0xFF, 0x10000);
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

} // namespace Gearnes
