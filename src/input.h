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

#ifndef INPUT_H_
#define	INPUT_H_

#include "common.h"

namespace Gearnes
{

enum NES_Keys
{
    kKeyUp,
    kKeyDown,
    kKeyLeft,
    kKeyRight,
    kKeyA,
    kKeyB,
    kKeySelect,
    kKeyStart
};

enum NES_Joypads
{
    kJoypad1,
    kJoypad2
};

class Input
{
public:
    Input();
    void Init();
    void Reset();
    void Tick(unsigned int clock_cycles);
    void KeyPressed(NES_Joypads joypad, NES_Keys key);
    void KeyReleased(NES_Joypads joypad, NES_Keys key);

private:
    void Update();
};

} // namespace Gearnes

#endif // INPUT_H_

