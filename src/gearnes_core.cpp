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

#include "gearnes_core.h"
#include "memory.h"
#include "audio.h"
#include "video.h"
#include "input.h"
#include "cartridge.h"
#include "mapper.h"

GearnesCore::GearnesCore()
{
    InitPointer(memory_);
    InitPointer(g6502_);
    InitPointer(audio_);
    InitPointer(video_);
    InitPointer(input_);
    InitPointer(cartridge_);
    for (int i = 0; i < 256; i++)
        InitPointer(mappers_[i]);
    paused_ = true;
}

GearnesCore::~GearnesCore()
{
#ifdef DEBUG_GEARNES
    if (cartridge_->IsReady())
    {
        Log("Saving Memory Dump...");

        using namespace std;

        char path[512];

        strcpy(path, cartridge_->GetFilePath());
        strcat(path, ".dump");

        memory_->MemoryDump(path);

        Log("Memory Dump Saved");
    }
#endif

    SafeDelete(cartridge_);
    SafeDelete(input_);
    SafeDelete(video_);
    SafeDelete(audio_);
    SafeDelete(g6502_);
    SafeDelete(memory_);
}

void GearnesCore::Init()
{
    Log("-=:: GEARNES %1.1f ::=-", GEARNES_VERSION);

    cartridge_ = new Cartridge();
    memory_ = new Memory(cartridge_);
    g6502_ = new g6502::G6502();
    audio_ = new Audio();
    video_ = new Video();
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

    bool loaded = cartridge_->LoadFromFile(path);
    if (loaded)
    {
        Reset();
        bool supported = SetupMapper();
        if (!supported)
        {
            Log("There was a problem loading the file: %s...", path);
        }
        return supported;
    }
    else
        return false;
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
        Log("Gearnes PAUSED");
    }
    else
    {
        Log("Gearnes RESUMED");
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
        Log("Gearnes RESET");
        Reset();
        SetupMapper();
    }
}

void GearnesCore::EnableSound(bool enabled)
{
    if (enabled)
    {
        Log("Gearnes sound ENABLED");
    }
    else
    {
        Log("Gearnes sound DISABLED");
    }
    audio_->Enable(enabled);
}

void GearnesCore::SetSoundSampleRate(int rate)
{
    Log("Gearnes sound sample rate: %d", rate);
    audio_->SetSampleRate(rate);
}

void GearnesCore::SaveRam()
{
    SaveRam(NULL);
}

void GearnesCore::SaveRam(const char* path)
{

}

void GearnesCore::LoadRam()
{
    LoadRam(NULL);
}

void GearnesCore::LoadRam(const char* path)
{

}

float GearnesCore::GetVersion()
{
    return GEARNES_VERSION;
}

void GearnesCore::InitMappers()
{

}

bool GearnesCore::SetupMapper()
{
    bool supported = true;
    u8 mapper = cartridge_->GetMapper();

    switch (mapper)
    {
        case 0:
            break;
        default:
            supported = false;
            break;
    }

    return true;
}

void GearnesCore::Reset()
{
    memory_->Reset();
    audio_->Reset();
    video_->Reset();
    input_->Reset();
    g6502_->Reset();
    paused_ = false;
}

