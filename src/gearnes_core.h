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

#ifndef GEARNESCORE_H_
#define GEARNESCORE_H_

#include "video.h"
#include "input.h"

enum NES_System
{
    kSystem_NTSC_USA,
    kSystem_NTSC_JAP,
    kSystem_PAL_EUR
};

//class Memory;
//class Processor;
class Audio;
class Cartridge;
//class SegaMemoryRule;
//class CodemastersMemoryRule;
//class RomOnlyMemoryRule;
//class MemoryRule;
//class SmsIOPorts;
//class GameGearIOPorts;

class GearnesCore
{
public:
    GearnesCore();
    ~GearnesCore();
    void Init();
    void RunToVBlank(NES_Color* frame_buffer);
    bool LoadROM(const char* path);
//    Memory* GetMemory();
    Cartridge* GetCartridge();
    void KeyPressed(NES_Joypads joypad, NES_Keys key);
    void KeyReleased(NES_Joypads joypad, NES_Keys key);
    void Pause(bool paused);
    bool IsPaused();
    void ResetROM();
    void EnableSound(bool enabled);
    void SetSoundSampleRate(int rate);
    void SaveRam();
    void SaveRam(const char* path);
    void LoadRam();
    void LoadRam(const char* path);
    float GetVersion();

private:
    void InitMemoryRules();
    bool AddMemoryRules();
    void Reset();

private:
//    Memory* m_pMemory;
//    Processor* m_pProcessor;
    Audio* audio_;
    Video* video_;
    Input* input_;
    Cartridge* cartridge_;
//    SegaMemoryRule* m_pSegaMemoryRule;
//    CodemastersMemoryRule* m_pCodemastersMemoryRule;
//    RomOnlyMemoryRule* m_pRomOnlyMemoryRule;
//    SmsIOPorts* m_pSmsIOPorts;
//    GameGearIOPorts* m_pGameGearIOPorts;
    bool paused_;
};

#endif // GEARNESCORE_H_

