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

#ifndef EMULATOR_H_
#define	EMULATOR_H_

#include <QMutex>
#include "../../../src/gearnes.h"

class Emulator
{
public:
    Emulator();
    ~Emulator();
    void Init();
    void RunToVBlank(Gearnes::NES_Color* frame_buffer);
    void LoadRom(const char* path);
    void KeyPressed(Gearnes::NES_Joypads joypad, Gearnes::NES_Keys key);
    void KeyReleased(Gearnes::NES_Joypads joypad, Gearnes::NES_Keys key);
    void Pause();
    void Resume();
    bool IsPaused();
    void Reset();
    void MemoryDump();
    void SetSoundSettings(bool enabled, int rate);
    void SaveRam();

private:
    Gearnes::GearnesCore* gearnes_core_;
    QMutex mutex_;
};

#endif // EMULATOR_H_

