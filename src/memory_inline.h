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

#ifndef MEMORYINLINE_H
#define	MEMORYINLINE_H

inline u8 Memory::Read(u16 address)
{
    return current_mapper_->PerformRead(address);
}

inline void Memory::Write(u16 address, u8 value)
{
    current_mapper_->PerformWrite(address, value);
}

inline u8 Memory::Retrieve(u16 address)
{
    return map_[address];
}

inline void Memory::Load(u16 address, u8 value)
{
    map_[address] = value;
}

#endif	/* MEMORYINLINE_H */

