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

#include "Video.h"

Video::Video()
{
    
}

Video::~Video()
{
    
}

void Video::Init()
{
    Reset(false);
}

void Video::Reset(bool is_pal)
{

}

bool Video::Tick(unsigned int clock_cycles, NES_Color* frame_buffer)
{
    return true;
}

void Video::ScanLine(int line)
{
    
}
