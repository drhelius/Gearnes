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

#ifndef NROM_H
#define	NROM_H

#include <iostream>
#include "../mapper.h"

class Memory;
class Cartridge;

class NROMMapper : public Mapper
{
public:
    NROMMapper(Memory* memory, Cartridge* cartridge);
    virtual ~NROMMapper();
    virtual void Reset();
    virtual u8 PerformRead(u16 address);
    virtual void PerformWrite(u16 address, u8 value);
};

#endif	/* NROM_H */
