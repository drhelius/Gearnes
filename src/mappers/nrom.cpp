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

#include "nrom.h"
#include "../cartridge.h"

NROMMapper::NROMMapper(Memory* memory, Cartridge* cartridge) : Mapper(memory,                                                                           cartridge)
{

}

NROMMapper::~NROMMapper()
{

}

void NROMMapper::Reset()
{

}

u8 NROMMapper::PerformRead(u16 address)
{
    if (address < 0x8000)
    {
        Log("NROM Reading $%04X", address);

        return 0xFF;
    }
    else if (cartridge_->GetPRGROMSize() == 0x4000)
    {
        return cartridge_->GetPRGROM()[(address & 0x3FFF)];
    }
    else
    {
        return cartridge_->GetPRGROM()[address & 0x7FFF];
    }
}

void NROMMapper::PerformWrite(u16 address, u8 value)
{
    Log("NROM Writing to cartridge $%04X 0x%02X", address, value);
}
