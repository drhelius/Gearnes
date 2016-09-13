/*
 * G6502 - 6502 Emulator
 * Copyright (C) 2016  Ignacio Sanchez Gines

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

#ifndef G6502_SIXTEENBITREGISTER_H_
#define	G6502_SIXTEENBITREGISTER_H_

#include "g6502_definitions.h"

namespace g6502
{
    
class SixteenBitRegister
{
public:
    SixteenBitRegister() : value_(0) { }
    void SetLow(u8 low);
    u8 GetLow() const;
    void SetHigh(u8 high);
    u8 GetHigh() const;
    void SetValue(u16 value);
    u16 GetValue() const;
    void Increment();
    void Decrement();

private:
    u16 value_;
};

inline void SixteenBitRegister::SetLow(u8 low)
{
    value_ = (value_ & 0xFF00) | low;
}

inline u8 SixteenBitRegister::GetLow() const
{
    return static_cast<u8>(value_ & 0x00FF);
}

inline void SixteenBitRegister::SetHigh(u8 high)
{
    value_ = (high << 8) | (value_ & 0x00FF);
}

inline u8 SixteenBitRegister::GetHigh() const
{
    return static_cast<u8>((value_ >> 8) & 0x00FF);
}

inline void SixteenBitRegister::SetValue(u16 value)
{
    value_ = value;
}

inline u16 SixteenBitRegister::GetValue() const
{
    return value_;
}

inline void SixteenBitRegister::Increment()
{
    value_++;
}

inline void SixteenBitRegister::Decrement()
{
    value_--;
}

} // namespace g6502

#endif // G6502_SIXTEENBITREGISTER_H_

