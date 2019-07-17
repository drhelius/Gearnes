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

#include <cstring>
#include "video.h"

namespace Gearnes
{

Video::Video()
{
    memset(registers_, 0, 8);
    latch_ = 0x00;
}

Video::~Video()
{
    
}

void Video::Init()
{
    Reset();
}

void Video::Reset()
{
    registers_[0] = 0x00;
    registers_[1] = 0x00;
    registers_[2] = 0xA0;
    registers_[3] = 0x00;
    registers_[4] = 0x00;
    registers_[5] = 0x00;
    registers_[6] = 0x00;
    registers_[7] = 0x00;

    latch_ = 0x00;
}

bool Video::Tick(unsigned int clock_cycles, NES_Color* frame_buffer)
{
    return true;
}

void Video::ScanLine(int line)
{
    
}

u8 Video::Read(u16 address)
{
    switch (address)
    {
        case 2:
        case 4:
        case 7:
        {
            latch_ = registers_[address];
            return latch_;
        }
        default:
        {
            return latch_;
        }
    }
}

void Video::Write(u16 address, u8 value)
{
    latch_ = value;

    switch (address)
    {
        case 2:
        {
            Log("Writing to PPU register $%02X: 0x%02X, address, value");
            break;
        }
        case 5:
        case 6:
        {
            registers_[address] = latch_;
            break;
        }
        default:
        {
            registers_[address] = latch_;
        }
    }
}

} // namespace Gearnes
