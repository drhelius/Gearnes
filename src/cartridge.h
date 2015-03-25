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

#ifndef CARTRIDGE_H_
#define	CARTRIDGE_H_

#include "definitions.h"

class Cartridge
{
public:
    Cartridge();
    ~Cartridge();
    void Init();
    void Reset();
    bool IsValid() const;
    bool IsReady() const;
    const char* GetFilePath() const;
    const char* GetFileName() const;
    u8* GetPRGROM() const;
    int GetPRGROMSize() const;
    int GetPRGROMBankCount() const;
    u8* GetCHRROM() const;
    int GetCHRROMSize() const;
    int GetCHRROMBankCount() const;
    u8* GetTrainer() const;
    bool LoadFromFile(const char* path);
    bool LoadFromBuffer(const u8* buffer, int size);
    u8 GetMapper() const;

private:
    bool GatherMetadata();
    bool LoadFromZipFile(const u8* buffer, int size);
    bool TestValid();

private:
    u8* header_;
    u8* prg_rom_;
    u8* chr_rom_;
    u8* trainer_;
    int prg_rom_size_;
    int prg_rom_bank_count_;
    int chr_rom_size_;
    int chr_rom_bank_count_;
    bool valid_;
    bool ready_;
    char file_path_[512];
    char file_name_[512];
    bool trainer_present_;
    bool battery_present_;
    u8 mapper_;
};

#endif // CARTRIDGE_H_
