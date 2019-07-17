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
#include "gearnes_core.h"
#include "memory.h"
#include "audio.h"
#include "video.h"
#include "input.h"
#include "cartridge.h"
#include "mapper.h"
#include "mappers/nrom.h"

namespace Gearnes
{

GearnesCore::GearnesCore()
{
    InitPointer(memory_);
    InitPointer(g6502_);
    InitPointer(audio_);
    InitPointer(video_);
    InitPointer(input_);
    InitPointer(cartridge_);

    for (int i = 0; i < 256; i++)
    {
        InitPointer(mappers_[i]);
    }

    paused_ = true;
    current_mapper_ = 0;
}

GearnesCore::~GearnesCore()
{

    MemoryDump();

    for (int i = 0; i < 256; i++)
    {
        SafeDelete(mappers_[i]);
    }

    SafeDelete(cartridge_);
    SafeDelete(input_);
    SafeDelete(video_);
    SafeDelete(audio_);
    SafeDelete(g6502_);
    SafeDelete(memory_);
}

void GearnesCore::Init()
{
    Log("-=:: %s ::=-", GEARNES_TITLE);

    cartridge_ = new Cartridge();
    video_ = new Video();
    memory_ = new Memory(video_);
    g6502_ = new g6502::G6502();
    audio_ = new Audio();    
    input_ = new Input();

    cartridge_->Init();
    memory_->Init();
    g6502_->Init(memory_);
    audio_->Init();
    video_->Init();
    input_->Init();

    InitMappers();
}

void GearnesCore::RunToVBlank(NES_Color* frame_buffer)
{
    if (!paused_ && cartridge_->IsReady())
    {
        bool vblank = false;
        while (!vblank)
        {
            unsigned int clock_cycles = g6502_->Tick();
            vblank = video_->Tick(clock_cycles, frame_buffer);
            audio_->Tick(clock_cycles);
            input_->Tick(clock_cycles);
        }
        audio_->EndFrame();
    }
}

bool GearnesCore::LoadROM(const char* path)
{
    MemoryDump();

    bool loaded = cartridge_->LoadFromFile(path);

    Reset();

    return loaded;
}

Memory* GearnesCore::GetMemory()
{
    return memory_;
}

Cartridge* GearnesCore::GetCartridge()
{
    return cartridge_;
}

void GearnesCore::KeyPressed(NES_Joypads joypad, NES_Keys key)
{
    input_->KeyPressed(joypad, key);
}

void GearnesCore::KeyReleased(NES_Joypads joypad, NES_Keys key)
{
    input_->KeyReleased(joypad, key);
}

void GearnesCore::Pause(bool paused)
{
    if (paused)
    {
        Log("PAUSED");
    }
    else
    {
        Log("RESUMED");
    }
    paused_ = paused;
}

bool GearnesCore::IsPaused()
{
    return paused_;
}

void GearnesCore::ResetROM()
{
    if (cartridge_->IsReady())
    {
        Log("RESET");
        Reset();
    }
}

void GearnesCore::EnableSound(bool enabled)
{
    if (enabled)
    {
        Log("Sound ENABLED");
    }
    else
    {
        Log("Sound DISABLED");
    }
    audio_->Enable(enabled);
}

void GearnesCore::SetSoundSampleRate(int rate)
{
    Log("Sound sample rate: %d", rate);
    audio_->SetSampleRate(rate);
}

void GearnesCore::SaveRam()
{
    SaveRam(nullptr);
}

void GearnesCore::SaveRam(const char* path)
{

}

void GearnesCore::LoadRam()
{
    LoadRam(nullptr);
}

void GearnesCore::LoadRam(const char* path)
{

}

float GearnesCore::GetVersion()
{
    return GEARNES_VERSION;
}

bool GearnesCore::SetupMapper()
{
    bool supported = true;
    u8 mapper = cartridge_->GetMapper();

    switch (mapper)
    {
        case 0:
            current_mapper_ = mapper;
            break;
        default:
            supported = false;
            current_mapper_ = 0;
            Log("Mapper not supported: %d", mapper);
            break;
    }

    memory_->SetCurrentMapper(mappers_[current_mapper_]);

    return supported;
}

void GearnesCore::Reset()
{
    memory_->Reset();
    SetupMapper();
    audio_->Reset();
    video_->Reset();
    input_->Reset();
    g6502_->Reset();
    paused_ = false;
}

void GearnesCore::MemoryDump()
{
#ifdef DEBUG_GEARNES
    if (cartridge_->IsReady())
    {
        Log("Saving Memory Dump...");

        using namespace std;

        char dmp_path[512];

        strcpy(dmp_path, cartridge_->GetFilePath());
        strcat(dmp_path, ".dump");

        memory_->MemoryDump(dmp_path);

        Log("Memory Dump Saved");
    }
#endif
}

void GearnesCore::InitMappers()
{
    for (int i = 0; i < 256; i++)
    {
        InitPointer(mappers_[i]);
    }

    mappers_[0] = new NROMMapper(memory_, cartridge_);
}

} // namespace Gearnes

