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

#include "g6502_core.h"
#include "g6502_definitions.h"
#include "g6502_eight_bit_register.h"
#include "g6502_sixteen_bit_register.h"
#include "g6502_opcode_names.h"
#include "g6502_opcode_timing.h"

namespace g6502 {

/// MUST INLINE --->>>
///
u8 G6502::ImmediateAddressing()
{
    return Fetch8();
}

u16 G6502::ZeroPageAddressing()
{
    return 0x00FF & Fetch8();
}

u16 G6502::ZeroPageXAddressing()
{
    return 0x00FF & (Fetch8() + X_.GetValue());
}

u16 G6502::ZeroPageYddressing()
{
    return 0x00FF & (Fetch8() + Y_.GetValue());
}

s8 G6502::RelativeAddressing()
{
    return static_cast<s8>(Fetch8());
}

u16 G6502::AbsoluteAddressing()
{
    return Fetch16();
}

u16 G6502::AbsoluteXAddressing()
{
    u16 address = Fetch16();
    u16 result = address + X_.GetValue();
    page_crossed_ = PageCrossed(address, result);
    return result;
}

u16 G6502::AbsoluteYAddressing()
{
    u16 address = Fetch16();
    u16 result = address + Y_.GetValue();
    page_crossed_ = PageCrossed(address, result);
    return result;
}

u16 G6502::IndirectAddressing()
{
    u16 address = Fetch16();
    u8 l = memory_impl_->Read(address);
    u8 h = memory_impl_->Read((address & 0xFF00) | ((address + 1) & 0x00FF));
    return MakeAddress16(h, l);
}

u16 G6502::IndexedIndirectAddressing()
{
    u16 address = Fetch8() + X_.GetValue();
    u8 l = memory_impl_->Read(address & 0x00FF);
    u8 h = memory_impl_->Read((address + 1) & 0x00FF);
    return MakeAddress16(h, l);
}

u16 G6502::IndirectIndexedAddressing()
{
    u16 address = Fetch8();
    u8 l = memory_impl_->Read(address);
    u8 h = memory_impl_->Read(address+1);
    address = MakeAddress16(h, l);
    u16 result = address + Y_.GetValue();
    page_crossed_ = PageCrossed(address, result);
    return result;
}

void G6502::OPCodes_ADC(u8 value)
{
    int result = A_.GetValue() + value + (IsSetFlag(FLAG_CARRY) ? 1 : 0);
    u8 final_result = static_cast<u8> (result);
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

void G6502::OPCodes_AND(u8 value)
{
    u8 result = A_.GetValue() & value;
    A_.SetValue(result);
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
}

void G6502::OPCodes_ASL_Accumulator()
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

void G6502::OPCodes_ASL_Memory(u16 address)
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

void G6502::OPcodes_Branch(bool condition)
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

void G6502::OPCodes_BIT(u16 address)
{
    u8 value = Read(address);
    u8 result = A_.GetValue() & value;
    SetZeroFlagFromResult(result);
    SetOverflowFlagFromResult(value);
    SetNegativeFlagFromResult(value);
}

void G6502::OPCodes_BRK()
{
    StackPush(&PC_);
    SetFlag(FLAG_BRK);
    StackPush(&P_);
    SetFlag(FLAG_IRQ);
    PC_.SetLow(memory_impl_->Read(0xFFFE));
    PC_.SetHigh(memory_impl_->Read(0xFFFF));
}

void G6502::OPCodes_ClearFlag(u8 flag)
{
    ClearFlag(flag);
}

void G6502::OPCodes_SetFlag(u8 flag)
{
    SetFlag(flag);
}

void G6502::OPCodes_CMP(u8 value)
{
    u8 a = A_.GetValue();
    u8 result = a - value;
    SetZeroFlagFromResult(result);
    SetNegativeFlagFromResult(result);
    if (a >= value)
        SetFlag(FLAG_CARRY);
    else
        ClearFlag(FLAG_CARRY);
}

///
/// MUST INLINE <<<---

G6502::G6502()
{
    InitOPCodeFunctors();
    InitPointer(memory_impl_);
    t_states_ = 0;
    interrupt_asserted_ = false;
    nmi_interrupt_requested_ = false;
    page_crossed_ = false;
    branch_taken_ = false;
}

G6502::~G6502()
{
}

void G6502::Init(MemoryInterface *memory_impl)
{
    memory_impl_ = memory_impl;
}

void G6502::Reset()
{
    PC_.SetLow(memory_impl_->Read(0xFFFC));
    PC_.SetHigh(memory_impl_->Read(0xFFFD));
    A_.SetValue(0x00);
    X_.SetValue(0x00);
    Y_.SetValue(0x00);
    S_.SetValue(0xFD);
    P_.SetValue(0x34);
    t_states_ = 0;
    interrupt_asserted_ = false;
    nmi_interrupt_requested_ = false;
    page_crossed_ = false;
    branch_taken_ = false;
}

unsigned int G6502::RunFor(unsigned int t_states)
{
    unsigned int count = 0;
    
    while (count < t_states)
    {
        count += Tick();
    }
    
    return count;
}

unsigned int G6502::Tick()
{
    t_states_ = 0;
    page_crossed_ = false;
    branch_taken_ = false;
    
    if (nmi_interrupt_requested_)
    {
        nmi_interrupt_requested_ = false;
        StackPush(&PC_);
        ClearFlag(FLAG_BRK);
        StackPush(&P_);
        SetFlag(FLAG_IRQ);
        PC_.SetLow(memory_impl_->Read(0xFFFA));
        PC_.SetHigh(memory_impl_->Read(0xFFFB));
        t_states_ += 7;
        return t_states_;
    }
    else if (!IsSetFlag(FLAG_IRQ) && interrupt_asserted_)
    { 
        StackPush(&PC_);
        ClearFlag(FLAG_BRK);
        StackPush(&P_);
        SetFlag(FLAG_IRQ);
        PC_.SetLow(memory_impl_->Read(0xFFFE));
        PC_.SetHigh(memory_impl_->Read(0xFFFF));
        t_states_ += 7;
        return t_states_;
    } 

    u8 opcode = Fetch8();

#ifdef G6502_DISASM
    u16 opcode_address = PC_.GetValue() - 1;

    if (!memory_impl_->IsDisassembled(opcode_address))
    {
        memory_impl_->Disassemble(opcode_address, kOPCodeNames[opcode]);
    }
#endif

    (this->*opcodes_[opcode])();

    t_states_ += kOPCodeTStates[opcode];
    t_states_ += page_crossed_ ? kOPCodeTStatesCrossPaged[opcode] : 0;
    t_states_ += branch_taken_ ? 1 : 0;

    return t_states_;
}

void G6502::RequestIRQ(bool assert)
{
    interrupt_asserted_ = assert;
}

void G6502::RequestNMI()
{
    nmi_interrupt_requested_ = true;
}

void G6502::UnofficialOPCode()
{
#ifdef G6502_DEBUG
    u16 opcode_address = PC_.GetValue() - 1;
    u8 opcode = memory_impl_->Read(opcode_address);
    Log("--> ** UNOFFICIAL OP Code (%X) at $%.4X -- %s", opcode, opcode_address, kOPCodeNames[opcode]);
#endif
}

void G6502::InitOPCodeFunctors()
{
    opcodes_[0x00] = &G6502::OPCode0x00;
    opcodes_[0x01] = &G6502::OPCode0x01;
    opcodes_[0x02] = &G6502::OPCode0x02;
    opcodes_[0x03] = &G6502::OPCode0x03;
    opcodes_[0x04] = &G6502::OPCode0x04;
    opcodes_[0x05] = &G6502::OPCode0x05;
    opcodes_[0x06] = &G6502::OPCode0x06;
    opcodes_[0x07] = &G6502::OPCode0x07;
    opcodes_[0x08] = &G6502::OPCode0x08;
    opcodes_[0x09] = &G6502::OPCode0x09;
    opcodes_[0x0A] = &G6502::OPCode0x0A;
    opcodes_[0x0B] = &G6502::OPCode0x0B;
    opcodes_[0x0C] = &G6502::OPCode0x0C;
    opcodes_[0x0D] = &G6502::OPCode0x0D;
    opcodes_[0x0E] = &G6502::OPCode0x0E;
    opcodes_[0x0F] = &G6502::OPCode0x0F;

    opcodes_[0x10] = &G6502::OPCode0x10;
    opcodes_[0x11] = &G6502::OPCode0x11;
    opcodes_[0x12] = &G6502::OPCode0x12;
    opcodes_[0x13] = &G6502::OPCode0x13;
    opcodes_[0x14] = &G6502::OPCode0x14;
    opcodes_[0x15] = &G6502::OPCode0x15;
    opcodes_[0x16] = &G6502::OPCode0x16;
    opcodes_[0x17] = &G6502::OPCode0x17;
    opcodes_[0x18] = &G6502::OPCode0x18;
    opcodes_[0x19] = &G6502::OPCode0x19;
    opcodes_[0x1A] = &G6502::OPCode0x1A;
    opcodes_[0x1B] = &G6502::OPCode0x1B;
    opcodes_[0x1C] = &G6502::OPCode0x1C;
    opcodes_[0x1D] = &G6502::OPCode0x1D;
    opcodes_[0x1E] = &G6502::OPCode0x1E;
    opcodes_[0x1F] = &G6502::OPCode0x1F;

    opcodes_[0x20] = &G6502::OPCode0x20;
    opcodes_[0x21] = &G6502::OPCode0x21;
    opcodes_[0x22] = &G6502::OPCode0x22;
    opcodes_[0x23] = &G6502::OPCode0x23;
    opcodes_[0x24] = &G6502::OPCode0x24;
    opcodes_[0x25] = &G6502::OPCode0x25;
    opcodes_[0x26] = &G6502::OPCode0x26;
    opcodes_[0x27] = &G6502::OPCode0x27;
    opcodes_[0x28] = &G6502::OPCode0x28;
    opcodes_[0x29] = &G6502::OPCode0x29;
    opcodes_[0x2A] = &G6502::OPCode0x2A;
    opcodes_[0x2B] = &G6502::OPCode0x2B;
    opcodes_[0x2C] = &G6502::OPCode0x2C;
    opcodes_[0x2D] = &G6502::OPCode0x2D;
    opcodes_[0x2E] = &G6502::OPCode0x2E;
    opcodes_[0x2F] = &G6502::OPCode0x2F;

    opcodes_[0x30] = &G6502::OPCode0x30;
    opcodes_[0x31] = &G6502::OPCode0x31;
    opcodes_[0x32] = &G6502::OPCode0x32;
    opcodes_[0x33] = &G6502::OPCode0x33;
    opcodes_[0x34] = &G6502::OPCode0x34;
    opcodes_[0x35] = &G6502::OPCode0x35;
    opcodes_[0x36] = &G6502::OPCode0x36;
    opcodes_[0x37] = &G6502::OPCode0x37;
    opcodes_[0x38] = &G6502::OPCode0x38;
    opcodes_[0x39] = &G6502::OPCode0x39;
    opcodes_[0x3A] = &G6502::OPCode0x3A;
    opcodes_[0x3B] = &G6502::OPCode0x3B;
    opcodes_[0x3C] = &G6502::OPCode0x3C;
    opcodes_[0x3D] = &G6502::OPCode0x3D;
    opcodes_[0x3E] = &G6502::OPCode0x3E;
    opcodes_[0x3F] = &G6502::OPCode0x3F;

    opcodes_[0x40] = &G6502::OPCode0x40;
    opcodes_[0x41] = &G6502::OPCode0x41;
    opcodes_[0x42] = &G6502::OPCode0x42;
    opcodes_[0x43] = &G6502::OPCode0x43;
    opcodes_[0x44] = &G6502::OPCode0x44;
    opcodes_[0x45] = &G6502::OPCode0x45;
    opcodes_[0x46] = &G6502::OPCode0x46;
    opcodes_[0x47] = &G6502::OPCode0x47;
    opcodes_[0x48] = &G6502::OPCode0x48;
    opcodes_[0x49] = &G6502::OPCode0x49;
    opcodes_[0x4A] = &G6502::OPCode0x4A;
    opcodes_[0x4B] = &G6502::OPCode0x4B;
    opcodes_[0x4C] = &G6502::OPCode0x4C;
    opcodes_[0x4D] = &G6502::OPCode0x4D;
    opcodes_[0x4E] = &G6502::OPCode0x4E;
    opcodes_[0x4F] = &G6502::OPCode0x4F;

    opcodes_[0x50] = &G6502::OPCode0x50;
    opcodes_[0x51] = &G6502::OPCode0x51;
    opcodes_[0x52] = &G6502::OPCode0x52;
    opcodes_[0x53] = &G6502::OPCode0x53;
    opcodes_[0x54] = &G6502::OPCode0x54;
    opcodes_[0x55] = &G6502::OPCode0x55;
    opcodes_[0x56] = &G6502::OPCode0x56;
    opcodes_[0x57] = &G6502::OPCode0x57;
    opcodes_[0x58] = &G6502::OPCode0x58;
    opcodes_[0x59] = &G6502::OPCode0x59;
    opcodes_[0x5A] = &G6502::OPCode0x5A;
    opcodes_[0x5B] = &G6502::OPCode0x5B;
    opcodes_[0x5C] = &G6502::OPCode0x5C;
    opcodes_[0x5D] = &G6502::OPCode0x5D;
    opcodes_[0x5E] = &G6502::OPCode0x5E;
    opcodes_[0x5F] = &G6502::OPCode0x5F;

    opcodes_[0x60] = &G6502::OPCode0x60;
    opcodes_[0x61] = &G6502::OPCode0x61;
    opcodes_[0x62] = &G6502::OPCode0x62;
    opcodes_[0x63] = &G6502::OPCode0x63;
    opcodes_[0x64] = &G6502::OPCode0x64;
    opcodes_[0x65] = &G6502::OPCode0x65;
    opcodes_[0x66] = &G6502::OPCode0x66;
    opcodes_[0x67] = &G6502::OPCode0x67;
    opcodes_[0x68] = &G6502::OPCode0x68;
    opcodes_[0x69] = &G6502::OPCode0x69;
    opcodes_[0x6A] = &G6502::OPCode0x6A;
    opcodes_[0x6B] = &G6502::OPCode0x6B;
    opcodes_[0x6C] = &G6502::OPCode0x6C;
    opcodes_[0x6D] = &G6502::OPCode0x6D;
    opcodes_[0x6E] = &G6502::OPCode0x6E;
    opcodes_[0x6F] = &G6502::OPCode0x6F;

    opcodes_[0x70] = &G6502::OPCode0x70;
    opcodes_[0x71] = &G6502::OPCode0x71;
    opcodes_[0x72] = &G6502::OPCode0x72;
    opcodes_[0x73] = &G6502::OPCode0x73;
    opcodes_[0x74] = &G6502::OPCode0x74;
    opcodes_[0x75] = &G6502::OPCode0x75;
    opcodes_[0x76] = &G6502::OPCode0x76;
    opcodes_[0x77] = &G6502::OPCode0x77;
    opcodes_[0x78] = &G6502::OPCode0x78;
    opcodes_[0x79] = &G6502::OPCode0x79;
    opcodes_[0x7A] = &G6502::OPCode0x7A;
    opcodes_[0x7B] = &G6502::OPCode0x7B;
    opcodes_[0x7C] = &G6502::OPCode0x7C;
    opcodes_[0x7D] = &G6502::OPCode0x7D;
    opcodes_[0x7E] = &G6502::OPCode0x7E;
    opcodes_[0x7F] = &G6502::OPCode0x7F;

    opcodes_[0x80] = &G6502::OPCode0x80;
    opcodes_[0x81] = &G6502::OPCode0x81;
    opcodes_[0x82] = &G6502::OPCode0x82;
    opcodes_[0x83] = &G6502::OPCode0x83;
    opcodes_[0x84] = &G6502::OPCode0x84;
    opcodes_[0x85] = &G6502::OPCode0x85;
    opcodes_[0x86] = &G6502::OPCode0x86;
    opcodes_[0x87] = &G6502::OPCode0x87;
    opcodes_[0x88] = &G6502::OPCode0x88;
    opcodes_[0x89] = &G6502::OPCode0x89;
    opcodes_[0x8A] = &G6502::OPCode0x8A;
    opcodes_[0x8B] = &G6502::OPCode0x8B;
    opcodes_[0x8C] = &G6502::OPCode0x8C;
    opcodes_[0x8D] = &G6502::OPCode0x8D;
    opcodes_[0x8E] = &G6502::OPCode0x8E;
    opcodes_[0x8F] = &G6502::OPCode0x8F;

    opcodes_[0x90] = &G6502::OPCode0x90;
    opcodes_[0x91] = &G6502::OPCode0x91;
    opcodes_[0x92] = &G6502::OPCode0x92;
    opcodes_[0x93] = &G6502::OPCode0x93;
    opcodes_[0x94] = &G6502::OPCode0x94;
    opcodes_[0x95] = &G6502::OPCode0x95;
    opcodes_[0x96] = &G6502::OPCode0x96;
    opcodes_[0x97] = &G6502::OPCode0x97;
    opcodes_[0x98] = &G6502::OPCode0x98;
    opcodes_[0x99] = &G6502::OPCode0x99;
    opcodes_[0x9A] = &G6502::OPCode0x9A;
    opcodes_[0x9B] = &G6502::OPCode0x9B;
    opcodes_[0x9C] = &G6502::OPCode0x9C;
    opcodes_[0x9D] = &G6502::OPCode0x9D;
    opcodes_[0x9E] = &G6502::OPCode0x9E;
    opcodes_[0x9F] = &G6502::OPCode0x9F;

    opcodes_[0xA0] = &G6502::OPCode0xA0;
    opcodes_[0xA1] = &G6502::OPCode0xA1;
    opcodes_[0xA2] = &G6502::OPCode0xA2;
    opcodes_[0xA3] = &G6502::OPCode0xA3;
    opcodes_[0xA4] = &G6502::OPCode0xA4;
    opcodes_[0xA5] = &G6502::OPCode0xA5;
    opcodes_[0xA6] = &G6502::OPCode0xA6;
    opcodes_[0xA7] = &G6502::OPCode0xA7;
    opcodes_[0xA8] = &G6502::OPCode0xA8;
    opcodes_[0xA9] = &G6502::OPCode0xA9;
    opcodes_[0xAA] = &G6502::OPCode0xAA;
    opcodes_[0xAB] = &G6502::OPCode0xAB;
    opcodes_[0xAC] = &G6502::OPCode0xAC;
    opcodes_[0xAD] = &G6502::OPCode0xAD;
    opcodes_[0xAE] = &G6502::OPCode0xAE;
    opcodes_[0xAF] = &G6502::OPCode0xAF;

    opcodes_[0xB0] = &G6502::OPCode0xB0;
    opcodes_[0xB1] = &G6502::OPCode0xB1;
    opcodes_[0xB2] = &G6502::OPCode0xB2;
    opcodes_[0xB3] = &G6502::OPCode0xB3;
    opcodes_[0xB4] = &G6502::OPCode0xB4;
    opcodes_[0xB5] = &G6502::OPCode0xB5;
    opcodes_[0xB6] = &G6502::OPCode0xB6;
    opcodes_[0xB7] = &G6502::OPCode0xB7;
    opcodes_[0xB8] = &G6502::OPCode0xB8;
    opcodes_[0xB9] = &G6502::OPCode0xB9;
    opcodes_[0xBA] = &G6502::OPCode0xBA;
    opcodes_[0xBB] = &G6502::OPCode0xBB;
    opcodes_[0xBC] = &G6502::OPCode0xBC;
    opcodes_[0xBD] = &G6502::OPCode0xBD;
    opcodes_[0xBE] = &G6502::OPCode0xBE;
    opcodes_[0xBF] = &G6502::OPCode0xBF;

    opcodes_[0xC0] = &G6502::OPCode0xC0;
    opcodes_[0xC1] = &G6502::OPCode0xC1;
    opcodes_[0xC2] = &G6502::OPCode0xC2;
    opcodes_[0xC3] = &G6502::OPCode0xC3;
    opcodes_[0xC4] = &G6502::OPCode0xC4;
    opcodes_[0xC5] = &G6502::OPCode0xC5;
    opcodes_[0xC6] = &G6502::OPCode0xC6;
    opcodes_[0xC7] = &G6502::OPCode0xC7;
    opcodes_[0xC8] = &G6502::OPCode0xC8;
    opcodes_[0xC9] = &G6502::OPCode0xC9;
    opcodes_[0xCA] = &G6502::OPCode0xCA;
    opcodes_[0xCB] = &G6502::OPCode0xCB;
    opcodes_[0xCC] = &G6502::OPCode0xCC;
    opcodes_[0xCD] = &G6502::OPCode0xCD;
    opcodes_[0xCE] = &G6502::OPCode0xCE;
    opcodes_[0xCF] = &G6502::OPCode0xCF;

    opcodes_[0xD0] = &G6502::OPCode0xD0;
    opcodes_[0xD1] = &G6502::OPCode0xD1;
    opcodes_[0xD2] = &G6502::OPCode0xD2;
    opcodes_[0xD3] = &G6502::OPCode0xD3;
    opcodes_[0xD4] = &G6502::OPCode0xD4;
    opcodes_[0xD5] = &G6502::OPCode0xD5;
    opcodes_[0xD6] = &G6502::OPCode0xD6;
    opcodes_[0xD7] = &G6502::OPCode0xD7;
    opcodes_[0xD8] = &G6502::OPCode0xD8;
    opcodes_[0xD9] = &G6502::OPCode0xD9;
    opcodes_[0xDA] = &G6502::OPCode0xDA;
    opcodes_[0xDB] = &G6502::OPCode0xDB;
    opcodes_[0xDC] = &G6502::OPCode0xDC;
    opcodes_[0xDD] = &G6502::OPCode0xDD;
    opcodes_[0xDE] = &G6502::OPCode0xDE;
    opcodes_[0xDF] = &G6502::OPCode0xDF;

    opcodes_[0xE0] = &G6502::OPCode0xE0;
    opcodes_[0xE1] = &G6502::OPCode0xE1;
    opcodes_[0xE2] = &G6502::OPCode0xE2;
    opcodes_[0xE3] = &G6502::OPCode0xE3;
    opcodes_[0xE4] = &G6502::OPCode0xE4;
    opcodes_[0xE5] = &G6502::OPCode0xE5;
    opcodes_[0xE6] = &G6502::OPCode0xE6;
    opcodes_[0xE7] = &G6502::OPCode0xE7;
    opcodes_[0xE8] = &G6502::OPCode0xE8;
    opcodes_[0xE9] = &G6502::OPCode0xE9;
    opcodes_[0xEA] = &G6502::OPCode0xEA;
    opcodes_[0xEB] = &G6502::OPCode0xEB;
    opcodes_[0xEC] = &G6502::OPCode0xEC;
    opcodes_[0xED] = &G6502::OPCode0xED;
    opcodes_[0xEE] = &G6502::OPCode0xEE;
    opcodes_[0xEF] = &G6502::OPCode0xEF;

    opcodes_[0xF0] = &G6502::OPCode0xF0;
    opcodes_[0xF1] = &G6502::OPCode0xF1;
    opcodes_[0xF2] = &G6502::OPCode0xF2;
    opcodes_[0xF3] = &G6502::OPCode0xF3;
    opcodes_[0xF4] = &G6502::OPCode0xF4;
    opcodes_[0xF5] = &G6502::OPCode0xF5;
    opcodes_[0xF6] = &G6502::OPCode0xF6;
    opcodes_[0xF7] = &G6502::OPCode0xF7;
    opcodes_[0xF8] = &G6502::OPCode0xF8;
    opcodes_[0xF9] = &G6502::OPCode0xF9;
    opcodes_[0xFA] = &G6502::OPCode0xFA;
    opcodes_[0xFB] = &G6502::OPCode0xFB;
    opcodes_[0xFC] = &G6502::OPCode0xFC;
    opcodes_[0xFD] = &G6502::OPCode0xFD;
    opcodes_[0xFE] = &G6502::OPCode0xFE;
    opcodes_[0xFF] = &G6502::OPCode0xFF;
}

} // namespace g6502
