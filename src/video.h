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

#ifndef VIDEO_H_
#define	VIDEO_H_

#include "definitions.h"

const int NES_WIDTH = 256;
const int NES_HEIGHT = 240;

struct NES_Color
{
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
};

class Video
{
public:
    Video();
    ~Video();
    void Init();
    void Reset(bool is_pal);
    bool Tick(unsigned int clock_cycles, NES_Color* frame_buffer);

private:
    void ScanLine(int line);
};

#endif // GD_VIDEO_H_

