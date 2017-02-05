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

#include <string>
#include <algorithm>
#include "cartridge.h"
#include "miniz/miniz.c"


Cartridge::Cartridge()
{
    InitPointer(prg_rom_);
    InitPointer(chr_rom_);
    InitPointer(trainer_);
    InitPointer(header_);
    valid_ = false;
    ready_ = false;
    file_path_[0] = 0;
    file_name_[0] = 0;
    prg_rom_size_ = 0;
    prg_rom_bank_count_ = 0;
    chr_rom_size_ = 0;
    chr_rom_bank_count_ = 0;
    trainer_present_ = false;
    battery_present_ = false;
    mapper_ = 0;
}

Cartridge::~Cartridge()
{
    SafeDeleteArray(prg_rom_);
    SafeDeleteArray(chr_rom_);
    SafeDeleteArray(trainer_);
    SafeDeleteArray(header_);
}

void Cartridge::Init()
{
    Reset();
}

void Cartridge::Reset()
{
    SafeDeleteArray(prg_rom_);
    SafeDeleteArray(chr_rom_);
    SafeDeleteArray(trainer_);
    SafeDeleteArray(header_);
    valid_ = false;
    ready_ = false;
    file_path_[0] = 0;
    file_name_[0] = 0;
    prg_rom_size_ = 0;
    prg_rom_bank_count_ = 0;
    chr_rom_size_ = 0;
    chr_rom_bank_count_ = 0;
    trainer_present_ = false;
    battery_present_ = false;
    mapper_ = 0;
}

bool Cartridge::IsValid() const
{
    return valid_;
}

bool Cartridge::IsReady() const
{
    return ready_;
}

u8* Cartridge::GetPRGROM() const
{
    return prg_rom_;
}

int Cartridge::GetPRGROMSize() const
{
    return prg_rom_size_;
}

int Cartridge::GetPRGROMBankCount() const
{
    return prg_rom_bank_count_;
}

u8* Cartridge::GetCHRROM() const
{
    return chr_rom_;
}

int Cartridge::GetCHRROMSize() const
{
    return chr_rom_size_;
}

int Cartridge::GetCHRROMBankCount() const
{
    return chr_rom_bank_count_;
}

u8* Cartridge::GetTrainer() const
{
    return trainer_;
}

const char* Cartridge::GetFilePath() const
{
    return file_path_;
}

const char* Cartridge::GetFileName() const
{
    return file_name_;
}

bool Cartridge::LoadFromZipFile(const u8* buffer, int size)
{
    using namespace std;

    mz_zip_archive zip_archive;
    mz_bool status;
    memset(&zip_archive, 0, sizeof (zip_archive));

    status = mz_zip_reader_init_mem(&zip_archive, (void*) buffer, size, 0);
    if (!status)
    {
        Log("mz_zip_reader_init_mem() failed!");
        return false;
    }

    for (unsigned int i = 0; i < mz_zip_reader_get_num_files(&zip_archive); i++)
    {
        mz_zip_archive_file_stat file_stat;
        if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat))
        {
            Log("mz_zip_reader_file_stat() failed!");
            mz_zip_reader_end(&zip_archive);
            return false;
        }

        Log("ZIP Content - Filename: \"%s\", Comment: \"%s\", Uncompressed size: %u, Compressed size: %u", file_stat.m_filename, file_stat.m_comment, (unsigned int) file_stat.m_uncomp_size, (unsigned int) file_stat.m_comp_size);

        string fn((const char*) file_stat.m_filename);
        transform(fn.begin(), fn.end(), fn.begin(), (int(*)(int)) tolower);
        string extension = fn.substr(fn.find_last_of(".") + 1);

        if (extension == "nes")
        {
            void *p;
            size_t uncomp_size;

            p = mz_zip_reader_extract_file_to_heap(&zip_archive, file_stat.m_filename, &uncomp_size, 0);
            if (!p)
            {
                Log("mz_zip_reader_extract_file_to_heap() failed!");
                mz_zip_reader_end(&zip_archive);
                return false;
            }

            bool ok = LoadFromBuffer((const u8*) p, uncomp_size);

            free(p);
            mz_zip_reader_end(&zip_archive);

            return ok;
        }
    }
    return false;
}

bool Cartridge::LoadFromFile(const char* path)
{
    using namespace std;

    Log("Loading %s...", path);

    Reset();

    strcpy(file_path_, path);

    std::string pathstr(path);
    std::string filename;

    size_t pos = pathstr.find_last_of("\\");
    if (pos != std::string::npos)
    {
        filename.assign(pathstr.begin() + pos + 1, pathstr.end());
    }
    else
    {
        pos = pathstr.find_last_of("/");
        if (pos != std::string::npos)
        {
            filename.assign(pathstr.begin() + pos + 1, pathstr.end());
        }
        else
        {
            filename = pathstr;
        }
    }
    
    strcpy(file_name_, filename.c_str());

    ifstream file(path, ios::in | ios::binary | ios::ate);

    if (file.is_open())
    {
        int size = static_cast<int> (file.tellg());
        char* memblock = new char[size];
        file.seekg(0, ios::beg);
        file.read(memblock, size);
        file.close();

        string fn(path);
        transform(fn.begin(), fn.end(), fn.begin(), (int(*)(int)) tolower);
        string extension = fn.substr(fn.find_last_of(".") + 1);

        if (extension == "zip")
        {
            Log("Loading from ZIP...");
            ready_ = LoadFromZipFile(reinterpret_cast<u8*> (memblock), size);
        }
        else
        {
            ready_ = LoadFromBuffer(reinterpret_cast<u8*> (memblock), size);
        }

        if (ready_)
        {
            Log("ROM loaded", path);
        }
        else
        {
            Log("There was a problem loading the memory for file %s...", path);
        }

        SafeDeleteArray(memblock);
    }
    else
    {
        Log("There was a problem loading the file %s...", path);
        ready_ = false;
    }

    if (!ready_)
    {
        Reset();
    }

    return ready_;
}

bool Cartridge::LoadFromBuffer(const u8* buffer, int size)
{
    if (IsValidPointer(buffer))
    {
        header_ = new u8[16];
        memcpy(header_, buffer, 16);

        int offset = 16;

        if (TestValid())
        {
            Log("ROM is Valid.");

            GatherMetadata();

            if (trainer_present_)
            {
                trainer_ = new u8[512];
                memcpy(trainer_, buffer + offset, 512);
                offset += 512;
            }

            prg_rom_ = new u8[prg_rom_size_];
            memcpy(prg_rom_, buffer + offset, prg_rom_size_);
            offset += prg_rom_size_;

            chr_rom_ = new u8[chr_rom_size_];
            memcpy(chr_rom_, buffer + offset, chr_rom_size_);

            return true;
        }
        else
        {
            Log("ROM is NOT Valid. No header found");
        }
    }

    return false;
}

u8 Cartridge::GetMapper() const
{
    return mapper_;
}

bool Cartridge::TestValid()
{
    return ((header_[0] == 0x4E) && (header_[1] == 0x45) && (header_[2] == 0x53) && (header_[3] == 0x1A));
}

bool Cartridge::GatherMetadata()
{
    prg_rom_bank_count_ = header_[4];
    chr_rom_bank_count_ = header_[5];
    u8 flags_6 = header_[6];
    u8 flags_7 = header_[7];
    u8 prg_ram_bank_count = header_[8];
    u8 flags_9 = header_[9];
    u8 flags_10 = header_[10];

    mapper_ = (flags_6 >> 4) | (flags_7 & 0xF0);
    Log("Mapper: %d", mapper_);

    prg_rom_size_ = prg_rom_bank_count_ * 16 * 1024;
    Log("PRG ROM, banks: %d size: %d", prg_rom_bank_count_, prg_rom_size_);

    chr_rom_size_ = chr_rom_bank_count_ * 8 * 1024;
    Log("CHR ROM, banks: %d size: %d", chr_rom_bank_count_, chr_rom_size_);

    Log("PRG RAM banks: %d", prg_ram_bank_count);

    battery_present_ = ((flags_6 & 0x02) != 0);
    Log("Battery: %s", battery_present_ ? "YES" : "NO");

    trainer_present_ = ((flags_6 & 0x04) != 0);
    Log("Trainer: %s", trainer_present_ ? "YES" : "NO");
}
