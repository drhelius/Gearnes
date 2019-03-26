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

#ifndef G6502_COREINL_H_
#define	G6502_COREINL_H_

#include "g6502_definitions.h"
#include "g6502_eight_bit_register.h"
#include "g6502_sixteen_bit_register.h"
#include "g6502_opcode_names.h"

namespace g6502
{
   
inline u8 G6502::Fetch8()
{
    u8 value = Read(PC_.GetValue());
    PC_.Increment();
    return value;
}

inline u16 G6502::Fetch16()
{
    u16 pc = PC_.GetValue();
    u8 l = Read(pc);
    u8 h = Read(pc + 1);
    PC_.SetValue(pc + 2);
    return Address16(h , l);
}

inline u16 G6502::Address16(u8 high, u8 low)
{
    return (high << 8 ) | low;
}

inline bool G6502::PageCrossed(u16 old_address, u16 new_address)
{
    return (old_address ^ new_address) > 0x00FF;
}

inline void G6502::ClearAllFlags()
{
    P_.SetValue(FLAG_NONE);
}

inline void G6502::SetZeroFlagFromResult(u8 result)
{
    if (result == 0)
        SetFlag(FLAG_ZERO);
    else
        ClearFlag(FLAG_ZERO);
}

inline void G6502::SetOverflowFlagFromResult(u8 result)
{
    P_.SetValue((P_.GetValue() & 0xBF) | (result & 0x40));
}

inline void G6502::SetNegativeFlagFromResult(u8 result)
{
    P_.SetValue((P_.GetValue() & 0x7F) | (result & 0x80));
}

inline void G6502::SetFlag(u8 flag)
{
    P_.SetValue(P_.GetValue() | flag);
}

inline void G6502::ClearFlag(u8 flag)
{
    P_.SetValue(P_.GetValue() & (~flag));
}

inline bool G6502::IsSetFlag(u8 flag)
{
    return (P_.GetValue() & flag) != 0;
}

inline void G6502::StackPush16(u16 value)
{
    Write(0x0100 | S_.GetValue(), static_cast<u8>((value >> 8) & 0x00FF));
    S_.Decrement();
    Write(0x0100 | S_.GetValue(), static_cast<u8>(value & 0x00FF));
    S_.Decrement();
}

inline void G6502::StackPush8(u8 value)
{
    Write(0x0100 | S_.GetValue(), value);
    S_.Decrement();
}

inline u16 G6502::StackPop16()
{
    S_.Increment();
    u8 l = Read(0x0100 | S_.GetValue());
    S_.Increment();
    u8 h = Read(0x0100 | S_.GetValue());
    return Address16(h , l);
}

inline u8 G6502::StackPop8()
{
    S_.Increment();
    u8 result = Read(0x0100 | S_.GetValue());
    return result;
}

inline u8 G6502::Read(u16 address)
{
    return memory_impl_->Read(address);
}

inline void G6502::Write(u16 address, u8 value)
{
    memory_impl_->Write(address, value);
}

inline u8 G6502::ImmediateAddressing()
{
    return Fetch8();
}

inline u16 G6502::ZeroPageAddressing()
{
    return 0x00FF & Fetch8();
}

inline u16 G6502::ZeroPageAddressing(EightBitRegister* reg)
{
    return 0x00FF & (Fetch8() + reg->GetValue());
}

inline s8 G6502::RelativeAddressing()
{
    return static_cast<s8>(Fetch8());
}

inline u16 G6502::AbsoluteAddressing()
{
    return Fetch16();
}

inline u16 G6502::AbsoluteAddressing(EightBitRegister* reg)
{
    u16 address = Fetch16();
    u16 result = address + reg->GetValue();
    page_crossed_ = PageCrossed(address, result);
    return result;
}

inline u16 G6502::IndirectAddressing()
{
    u16 address = Fetch16();
    u8 l = Read(address);
    u8 h = Read((address & 0xFF00) | ((address + 1) & 0x00FF));
    return Address16(h, l);
}

inline u16 G6502::IndexedIndirectAddressing()
{
    u16 address = Fetch8() + X_.GetValue();
    u8 l = Read(address & 0x00FF);
    u8 h = Read((address + 1) & 0x00FF);
    return Address16(h, l);
}

inline u16 G6502::IndirectIndexedAddressing()
{
    u16 address = Fetch8();
    u8 l = Read(address);
    u8 h = Read(address+1);
    address = Address16(h, l);
    u16 result = address + Y_.GetValue();
    page_crossed_ = PageCrossed(address, result);
    return result;
}

inline void G6502::OPCodes_ADC(u8 value)
{
    int result = A_.GetValue() + value + (IsSetFlag(FLAG_CARRY) ? 1 : 0);
    u8 final_result = static_cast<u8> (result & 0xFF);
    SetZeroFlagFromResult(final_result);
    SetNegativeFlagFromResult(final_result);
    if ((result & 0x100) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlag(FLAG_CARRY);
    if ((((A_.GetValue() ^ value) & 0x80) == 0) && (((A_.GetValue() ^ result) & 0x80) != 0))
        SetFlag(FLAG_OVERFLOW);
    else
        ClearFlag(FLAG_OVERFLOW);
    A_.SetValue(final_result);
}

inline void G6502::OPCodes_AND(u8 value)
{
    u8 result = A_.GetValue() & value;
    A_.SetValue(result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
}

inline void G6502::OPCodes_ASL_Accumulator()
{
    u8 value = A_.GetValue();
    u8 result = value << 1;
    A_.SetValue(result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
    if ((value & 0x80) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlag(FLAG_CARRY);
}

inline void G6502::OPCodes_ASL_Memory(u16 address)
{
    u8 value = Read(address);
    u8 result = value << 1;
    Write(address, result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
    if ((value & 0x80) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlag(FLAG_CARRY);
}

inline void G6502::OPcodes_Branch(bool condition)
{
    if (condition)
    {
        s8 displacement = RelativeAddressing();
        u16 address = PC_.GetValue();
        u16 result = address + displacement;
        PC_.SetValue(result);
        branch_taken_ = true;
        page_crossed_ = PageCrossed(address, result);
    }
    else
        PC_.Increment();
}

inline void G6502::OPCodes_BIT(u16 address)
{
    u8 value = Read(address);
    u8 result = A_.GetValue() & value;
    SetZeroFlagFromResult(result);
    SetOverflowFlagFromResult(value);
    SetNegativeFlagFromResult(value);
}

inline void G6502::OPCodes_BRK()
{
    StackPush16(PC_.GetValue());
    SetFlag(FLAG_BRK);
    StackPush8(P_.GetValue());
    SetFlag(FLAG_IRQ);
    PC_.SetLow(Read(0xFFFE));
    PC_.SetHigh(Read(0xFFFF));
}

inline void G6502::OPCodes_ClearFlag(u8 flag)
{
    ClearFlag(flag);
}

inline void G6502::OPCodes_SetFlag(u8 flag)
{
    SetFlag(flag);
}

inline void G6502::OPCodes_CMP(EightBitRegister* reg, u8 value)
{
    u8 reg_value = reg->GetValue();
    u8 result = reg_value - value;
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
    if (reg_value >= value)
        SetFlag(FLAG_CARRY);
    else
        ClearFlag(FLAG_CARRY);
}

inline void G6502::OPCodes_DEC_Mem(u16 address)
{
    u8 value = Read(address);
    u8 result = value - 1;
    Write(address, result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
}

inline void G6502::OPCodes_DEC_Reg(EightBitRegister* reg)
{
    u8 value = reg->GetValue();
    u8 result = value - 1;
    reg->SetValue(result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
}

inline void G6502::OPCodes_EOR(u8 value)
{
    u8 result = A_.GetValue() ^ value;
    A_.SetValue(result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
}

inline void G6502::OPCodes_INC_Mem(u16 address)
{
    u8 value = Read(address);
    u8 result = value + 1;
    Write(address, result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
}

inline void G6502::OPCodes_INC_Reg(EightBitRegister* reg)
{
    u8 value = reg->GetValue();
    u8 result = value + 1;
    reg->SetValue(result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
}

inline void G6502::OPCodes_LD(EightBitRegister* reg, u8 value)
{
    reg->SetValue(value);
    SetZeroFlagFromResult(value);
    SetNegativeFlagFromResult(value);
}

inline void G6502::OPCodes_LSR_Accumulator()
{
    u8 value = A_.GetValue();
    u8 result = value >> 1;
    A_.SetValue(result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
    if ((value & 0x01) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlag(FLAG_CARRY);
}

inline void G6502::OPCodes_LSR_Memory(u16 address)
{
    u8 value = Read(address);
    u8 result = value >> 1;
    Write(address, result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
    if ((value & 0x01) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlag(FLAG_CARRY);
}

inline void G6502::OPCodes_ORA(u8 value)
{
    u8 result = A_.GetValue() | value;
    A_.SetValue(result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
}

inline void G6502::OPCodes_ROL_Accumulator()
{
    u8 value = A_.GetValue();
    u8 result = value << 1;
    result |= IsSetFlag(FLAG_CARRY) ? 0x01 : 0x00;
    A_.SetValue(result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
    if ((value & 0x80) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlag(FLAG_CARRY);
}

inline void G6502::OPCodes_ROL_Memory(u16 address)
{
    u8 value = Read(address);
    u8 result = value << 1;
    result |= IsSetFlag(FLAG_CARRY) ? 0x01 : 0x00;
    Write(address, result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
    if ((value & 0x80) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlag(FLAG_CARRY);
}

inline void G6502::OPCodes_ROR_Accumulator()
{
    u8 value = A_.GetValue();
    u8 result = value >> 1;
    result |= IsSetFlag(FLAG_CARRY) ? 0x80 : 0x00;
    A_.SetValue(result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
    if ((value & 0x01) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlag(FLAG_CARRY);
}

inline void G6502::OPCodes_ROR_Memory(u16 address)
{
    u8 value = Read(address);
    u8 result = value >> 1;
    result |= IsSetFlag(FLAG_CARRY) ? 0x80 : 0x00;
    Write(address, result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
    if ((value & 0x01) != 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlag(FLAG_CARRY);
}

inline void G6502::OPCodes_SBC(u8 value)
{
    int result = A_.GetValue() - value - (IsSetFlag(FLAG_CARRY) ? 0x00 : 0x01);
    u8 final_result = static_cast<u8> (result & 0xFF);
    SetZeroFlagFromResult(final_result);
    SetNegativeFlagFromResult(final_result);
    if ((result & 0x100) == 0)
        SetFlag(FLAG_CARRY);
    else
        ClearFlag(FLAG_CARRY);
    if ((((A_.GetValue() ^ value) & 0x80) != 0) && (((A_.GetValue() ^ result) & 0x80) != 0))
        SetFlag(FLAG_OVERFLOW);
    else
        ClearFlag(FLAG_OVERFLOW);
    A_.SetValue(final_result);
}

inline void G6502::OPCodes_Store(EightBitRegister* reg, u16 address)
{
    u8 value = reg->GetValue();
    Write(address, value);
}

inline void G6502::OPCodes_Transfer(EightBitRegister* reg, EightBitRegister* target)
{
    u8 value = reg->GetValue();
    target->SetValue(value);
    SetZeroFlagFromResult(value);
    SetNegativeFlagFromResult(value);
}

} // namespace g6502

#endif // G6502_COREINL_H_

