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

#include "emulator.h"

Emulator::Emulator()
{
    InitPointer(gearnes_core_);
}

Emulator::~Emulator()
{
    SafeDelete(gearnes_core_);
}

void Emulator::Init()
{
    gearnes_core_ = new GearnesCore();
    gearnes_core_->Init();
}

void Emulator::LoadRom(const char* path)
{
    mutex_.lock();
    gearnes_core_->SaveRam();
    gearnes_core_->LoadROM(path);
    gearnes_core_->LoadRam();
    mutex_.unlock();
}

void Emulator::RunToVBlank(NES_Color* frame_buffer)
{
    mutex_.lock();
    gearnes_core_->RunToVBlank(frame_buffer);
    mutex_.unlock();
}

void Emulator::KeyPressed(NES_Joypads joypad, NES_Keys key)
{
    mutex_.lock();
    gearnes_core_->KeyPressed(joypad, key);
    mutex_.unlock();
}

void Emulator::KeyReleased(NES_Joypads joypad, NES_Keys key)
{
    mutex_.lock();
    gearnes_core_->KeyReleased(joypad, key);
    mutex_.unlock();
}

void Emulator::Pause()
{
    mutex_.lock();
    gearnes_core_->Pause(true);
    mutex_.unlock();
}

void Emulator::Resume()
{
    mutex_.lock();
    gearnes_core_->Pause(false);
    mutex_.unlock();
}

bool Emulator::IsPaused()
{
    mutex_.lock();
    bool paused = gearnes_core_->IsPaused();
    mutex_.unlock();
    return paused;
}

void Emulator::Reset()
{
    mutex_.lock();
    gearnes_core_->SaveRam();
    gearnes_core_->ResetROM();
    gearnes_core_->LoadRam();
    mutex_.unlock();
}

void Emulator::MemoryDump()
{
//    m_Mutex.lock();
//    m_pGearsystemCore->GetMemory()->MemoryDump("memdump.txt");
//    m_Mutex.unlock();
}

void Emulator::SetSoundSettings(bool enabled, int rate)
{
    mutex_.lock();
    gearnes_core_->EnableSound(enabled);
    gearnes_core_->SetSoundSampleRate(rate);
    mutex_.unlock();
}

void Emulator::SaveRam()
{
    mutex_.lock();
    gearnes_core_->SaveRam();
    mutex_.unlock();
}
