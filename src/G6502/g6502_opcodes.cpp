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

#include "g6502_definitions.h"
#include "g6502_eight_bit_register.h"
#include "g6502_sixteen_bit_register.h"
#include "g6502_core.h"

namespace g6502
{
   
void G6502::OPCode0x00()
{
    // BRK
    OPCodes_BRK();
}

void G6502::OPCode0x01()
{
    // ORA $(nn,X)
}

void G6502::OPCode0x02()
{
    // UNOFFICIAL
    // KILL
    UnofficialOPCode();
}

void G6502::OPCode0x03()
{
    // UNOFFICIAL
    // SLO $(nn,X)
    UnofficialOPCode();
}

void G6502::OPCode0x04()
{
    // UNOFFICIAL
    // NOP $n
    UnofficialOPCode();
}

void G6502::OPCode0x05()
{
    // ORA $n
}

void G6502::OPCode0x06()
{
    // ASL $n
    OPCodes_ASL_Memory(ZeroPageAddressing());
}

void G6502::OPCode0x07()
{
    // UNOFFICIAL
    // SLO $n
    UnofficialOPCode();
}

void G6502::OPCode0x08()
{
    // PHP
}

void G6502::OPCode0x09()
{
    // ORA #$n
}

void G6502::OPCode0x0A()
{
    // ASL A
    OPCodes_ASL_Accumulator();
}

void G6502::OPCode0x0B()
{
    // UNOFFICIAL
    // ANC #$n
    UnofficialOPCode();
}

void G6502::OPCode0x0C()
{
    // UNOFFICIAL
    // NOP $nn
    UnofficialOPCode();
}

void G6502::OPCode0x0D()
{
    // ORA $nn
}

void G6502::OPCode0x0E()
{
    // ASL $nn
    OPCodes_ASL_Memory(AbsoluteAddressing());
}

void G6502::OPCode0x0F()
{
    // UNOFFICIAL
    // SLO $nn
    UnofficialOPCode();
}

void G6502::OPCode0x10()
{
    // BPL $s
    OPcodes_Branch(!IsSetFlag(FLAG_NEGATIVE));
}

void G6502::OPCode0x11()
{
    // ORA ($n),Y
}

void G6502::OPCode0x12()
{
    // UNOFFICIAL
    // KILL
    UnofficialOPCode();
}

void G6502::OPCode0x13()
{
    // UNOFFICIAL
    // SLO ($n),Y
    UnofficialOPCode();
}

void G6502::OPCode0x14()
{
    // UNOFFICIAL
    // NOP $n,X
    UnofficialOPCode();
}

void G6502::OPCode0x15()
{
    // ORA $n,X
}

void G6502::OPCode0x16()
{
    // ASL $n,X
    OPCodes_ASL_Memory(ZeroPageXAddressing());
}

void G6502::OPCode0x17()
{
    // UNOFFICIAL
    // SLO $n,X
    UnofficialOPCode();
}

void G6502::OPCode0x18()
{
    // CLC
    OPCodes_ClearFlag(FLAG_CARRY);
}

void G6502::OPCode0x19()
{
    // ORA $nn,Y
}

void G6502::OPCode0x1A()
{
    // UNOFFICIAL
    // NOP
    UnofficialOPCode();
}

void G6502::OPCode0x1B()
{
    // UNOFFICIAL
    // SLO $nn,Y
    UnofficialOPCode();
}

void G6502::OPCode0x1C()
{
    // UNOFFICIAL
    // NOP $nn,X
    UnofficialOPCode();
}

void G6502::OPCode0x1D()
{
    // ORA $nn,X
}

void G6502::OPCode0x1E()
{
    // ASL $nn,X
    OPCodes_ASL_Memory(AbsoluteXAddressing());
}

void G6502::OPCode0x1F()
{
    // UNOFFICIAL
    // SLO $nn,X
    UnofficialOPCode();
}

void G6502::OPCode0x20()
{
    // JSR $nn
    u16 target = AbsoluteAddressing();
    StackPush16(PC_.GetValue() - 1);
    PC_.SetValue(target);
}

void G6502::OPCode0x21()
{
    // AND $(nn,X)
    OPCodes_AND(Read(IndexedIndirectAddressing()));
}

void G6502::OPCode0x22()
{
    // UNOFFICIAL
    // KILL
    UnofficialOPCode();
}

void G6502::OPCode0x23()
{
    // UNOFFICIAL
    // RLA $(nn,X)
    UnofficialOPCode();
}

void G6502::OPCode0x24()
{
    // BIT $n
    OPCodes_BIT(ZeroPageAddressing());
}

void G6502::OPCode0x25()
{
    // AND $n
    OPCodes_AND(Read(ZeroPageAddressing()));
}

void G6502::OPCode0x26()
{
    // ROL $n
}

void G6502::OPCode0x27()
{
    // UNOFFICIAL
    // RLA $n
    UnofficialOPCode();
}

void G6502::OPCode0x28()
{
    // PLP
}

void G6502::OPCode0x29()
{
    // AND #$n
    OPCodes_AND(ImmediateAddressing());
}

void G6502::OPCode0x2A()
{
    // ROL
}

void G6502::OPCode0x2B()
{
    // UNOFFICIAL
    // ANC #$n
    UnofficialOPCode();
}

void G6502::OPCode0x2C()
{
    // BIT $nn
    OPCodes_BIT(AbsoluteAddressing());
}

void G6502::OPCode0x2D()
{
    // AND $nn
    OPCodes_AND(Read(AbsoluteAddressing()));
}

void G6502::OPCode0x2E()
{
    // ROL $nn
}

void G6502::OPCode0x2F()
{
    // UNOFFICIAL
    // RLA $nn
    UnofficialOPCode();
}

void G6502::OPCode0x30()
{
    // BMI $s
    OPcodes_Branch(IsSetFlag(FLAG_NEGATIVE));
}

void G6502::OPCode0x31()
{
    // AND ($n),Y
    OPCodes_AND(Read(IndirectIndexedAddressing()));
}

void G6502::OPCode0x32()
{
    // UNOFFICIAL
    // KILL
    UnofficialOPCode();
}

void G6502::OPCode0x33()
{
    // UNOFFICIAL
    // RLA ($n),Y
    UnofficialOPCode();
}

void G6502::OPCode0x34()
{
    // UNOFFICIAL
    // NOP $n,X
    UnofficialOPCode();
}

void G6502::OPCode0x35()
{
    // AND $n,X
    OPCodes_AND(Read(ZeroPageXAddressing()));
}

void G6502::OPCode0x36()
{
    // ROL $n,X
}

void G6502::OPCode0x37()
{
    // UNOFFICIAL
    // RLA $n,X
    UnofficialOPCode();
}

void G6502::OPCode0x38()
{
    // SEC
    OPCodes_SetFlag(FLAG_CARRY);
}

void G6502::OPCode0x39()
{
    // AND $nn,Y
    OPCodes_AND(Read(AbsoluteYAddressing()));
}

void G6502::OPCode0x3A()
{
    // UNOFFICIAL
    // NOP
    UnofficialOPCode();
}

void G6502::OPCode0x3B()
{
    // UNOFFICIAL
    // RLA $nn,Y
    UnofficialOPCode();
}

void G6502::OPCode0x3C()
{
    // UNOFFICIAL
    // NOP $nn,X
    UnofficialOPCode();
}

void G6502::OPCode0x3D()
{
    // AND $nn,X
    OPCodes_AND(Read(AbsoluteXAddressing()));
}

void G6502::OPCode0x3E()
{
    // ROL $nn,X
}

void G6502::OPCode0x3F()
{
    // UNOFFICIAL
    // RLA $nn,X
    UnofficialOPCode();
}

void G6502::OPCode0x40()
{
    // RTI
}

void G6502::OPCode0x41()
{
    // EOR $(nn,X)
    OPCodes_EOR(Read(IndexedIndirectAddressing()));
}

void G6502::OPCode0x42()
{
    // UNOFFICIAL
    // KILL
    UnofficialOPCode();
}

void G6502::OPCode0x43()
{
    // UNOFFICIAL
    // SRE $(nn,X);
    UnofficialOPCode();
}

void G6502::OPCode0x44()
{
    // UNOFFICIAL
    // NOP $n
    UnofficialOPCode();
}

void G6502::OPCode0x45()
{
    // EOR $n
    OPCodes_EOR(Read(ZeroPageAddressing()));
}

void G6502::OPCode0x46()
{
    // LSR $n
    OPCodes_LSR_Memory(ZeroPageAddressing());
}

void G6502::OPCode0x47()
{
    // UNOFFICIAL
    // SRE $n
    UnofficialOPCode();
}

void G6502::OPCode0x48()
{
    // PHA
}

void G6502::OPCode0x49()
{
    // EOR #$n
    OPCodes_EOR(ImmediateAddressing());
}

void G6502::OPCode0x4A()
{
    // LSR
    OPCodes_LSR_Accumulator();
}

void G6502::OPCode0x4B()
{
    // UNOFFICIAL
    // ALR #$n
    UnofficialOPCode();
}

void G6502::OPCode0x4C()
{
    // JMP $nn
    PC_.SetValue(AbsoluteAddressing());
}

void G6502::OPCode0x4D()
{
    // EOR $nn
    OPCodes_EOR(Read(AbsoluteAddressing()));
}

void G6502::OPCode0x4E()
{
    // LSR $nn
    OPCodes_LSR_Memory(AbsoluteAddressing());
}

void G6502::OPCode0x4F()
{
    // UNOFFICIAL
    // SRE $nn
    UnofficialOPCode();
}

void G6502::OPCode0x50()
{
    // BVC $s
    OPcodes_Branch(!IsSetFlag(FLAG_OVERFLOW));
}

void G6502::OPCode0x51()
{
    // EOR ($n),Y
    OPCodes_EOR(Read(IndirectIndexedAddressing()));
}

void G6502::OPCode0x52()
{
    // UNOFFICIAL
    // KILL
    UnofficialOPCode();
}

void G6502::OPCode0x53()
{
    // UNOFFICIAL
    // SRE ($n),Y
    UnofficialOPCode();
}

void G6502::OPCode0x54()
{
    // UNOFFICIAL
    // NOP $n,X
    UnofficialOPCode();
}

void G6502::OPCode0x55()
{
    // EOR $n,X
    OPCodes_EOR(Read(ZeroPageXAddressing()));
}

void G6502::OPCode0x56()
{
    // LSR $n,X
    OPCodes_LSR_Memory(ZeroPageXAddressing());
}

void G6502::OPCode0x57()
{
    // UNOFFICIAL
    // SRE $n,X
    UnofficialOPCode();
}

void G6502::OPCode0x58()
{
    // CLI
    OPCodes_ClearFlag(FLAG_IRQ);
}

void G6502::OPCode0x59()
{
    // EOR $nn,Y
    OPCodes_EOR(Read(AbsoluteYAddressing()));
}

void G6502::OPCode0x5A()
{
    // UNOFFICIAL
    // NOP
    UnofficialOPCode();
}

void G6502::OPCode0x5B()
{
    // UNOFFICIAL
    // SRE $nn,Y
    UnofficialOPCode();
}

void G6502::OPCode0x5C()
{
    // UNOFFICIAL
    // NOP $nn,X
    UnofficialOPCode();
}

void G6502::OPCode0x5D()
{
    // EOR $nn,X
    OPCodes_EOR(Read(AbsoluteXAddressing()));
}

void G6502::OPCode0x5E()
{
    // LSR $nn,X
    OPCodes_LSR_Memory(AbsoluteXAddressing());
}

void G6502::OPCode0x5F()
{
    // UNOFFICIAL
    // SRE $nn,X
    UnofficialOPCode();
}

void G6502::OPCode0x60()
{
    // RTS
    PC_.SetValue(StackPop16() + 1);
}

void G6502::OPCode0x61()
{
    // ADC $(nn,X)
    OPCodes_ADC(Read(IndexedIndirectAddressing()));
}

void G6502::OPCode0x62()
{
    // UNOFFICIAL
    // KILL
    UnofficialOPCode();
}

void G6502::OPCode0x63()
{
    // UNOFFICIAL
    // RRA $(nn,X)
    UnofficialOPCode();
}

void G6502::OPCode0x64()
{
    // UNOFFICIAL
    // NOP $n
    UnofficialOPCode();
}

void G6502::OPCode0x65()
{
    // ADC $n
    OPCodes_ADC(Read(ZeroPageAddressing()));
}

void G6502::OPCode0x66()
{
    // ROR $n
}

void G6502::OPCode0x67()
{
    // UNOFFICIAL
    // RRA $n
    UnofficialOPCode();
}

void G6502::OPCode0x68()
{
    // PLA
}

void G6502::OPCode0x69()
{
    // ADC #$n
    OPCodes_ADC(ImmediateAddressing());
}

void G6502::OPCode0x6A()
{
    // ROR
}

void G6502::OPCode0x6B()
{
    // UNOFFICIAL
    // ARR #$n
    UnofficialOPCode();
}

void G6502::OPCode0x6C()
{
    // JMP ($nn)
    PC_.SetValue(IndirectAddressing());
}

void G6502::OPCode0x6D()
{
    // ADC $nn
    OPCodes_ADC(Read(AbsoluteAddressing()));
}

void G6502::OPCode0x6E()
{
    // ROR $nn
}

void G6502::OPCode0x6F()
{
    // UNOFFICIAL
    // RRA $nn
    UnofficialOPCode();
}

void G6502::OPCode0x70()
{
    // BVS $s
    OPcodes_Branch(IsSetFlag(FLAG_OVERFLOW));
}

void G6502::OPCode0x71()
{
    // ADC ($n),Y
    OPCodes_ADC(Read(IndirectIndexedAddressing()));
}

void G6502::OPCode0x72()
{
    // UNOFFICIAL
    // KILL
    UnofficialOPCode();
}

void G6502::OPCode0x73()
{
    // UNOFFICIAL
    // RRA ($n),Y
    UnofficialOPCode();
}

void G6502::OPCode0x74()
{
    // UNOFFICIAL
    // NOP $n,X
    UnofficialOPCode();
}

void G6502::OPCode0x75()
{
    // ADC $n,X
    OPCodes_ADC(Read(ZeroPageXAddressing()));
}

void G6502::OPCode0x76()
{
    // ROR $n,X
}

void G6502::OPCode0x77()
{
    // UNOFFICIAL
    // RRA $n,X
    UnofficialOPCode();
}

void G6502::OPCode0x78()
{
    // SEI
    OPCodes_SetFlag(FLAG_IRQ);
}

void G6502::OPCode0x79()
{
    // ADC $nn,Y
    OPCodes_ADC(Read(AbsoluteYAddressing()));
}

void G6502::OPCode0x7A()
{
    // UNOFFICIAL
    // NOP
    UnofficialOPCode();
}

void G6502::OPCode0x7B()
{
    // UNOFFICIAL
    // RRA $nn,Y
    UnofficialOPCode();
}

void G6502::OPCode0x7C()
{
    // UNOFFICIAL
    // NOP $nn,X
    UnofficialOPCode();
}

void G6502::OPCode0x7D()
{
    // ADC $nn,X
    OPCodes_ADC(Read(AbsoluteXAddressing()));
}

void G6502::OPCode0x7E()
{
    // ROR $nn,X
}

void G6502::OPCode0x7F()
{
    // UNOFFICIAL
    // RRA $nn,X
    UnofficialOPCode();
}

void G6502::OPCode0x80()
{
    // UNOFFICIAL
    // NOP #$n
    UnofficialOPCode();
}

void G6502::OPCode0x81()
{
    // STA $(nn,X)
}

void G6502::OPCode0x82()
{
    // UNOFFICIAL
    // NOP #$n
    UnofficialOPCode();
}

void G6502::OPCode0x83()
{
    // UNOFFICIAL
    // SAX $(nn,X)
    UnofficialOPCode();
}

void G6502::OPCode0x84()
{
    // STY $n
}

void G6502::OPCode0x85()
{
    // STA $n
}

void G6502::OPCode0x86()
{
    // STX $n
}

void G6502::OPCode0x87()
{
    // UNOFFICIAL
    // SAX $n
    UnofficialOPCode();
}

void G6502::OPCode0x88()
{
    // DEY
    OPCodes_DEC_Reg(&Y_);
}

void G6502::OPCode0x89()
{
    // UNOFFICIAL
    // NOP #$n
    UnofficialOPCode();
}

void G6502::OPCode0x8A()
{
    // TXA
}

void G6502::OPCode0x8B()
{
    // UNOFFICIAL
    // XAA #$n
    UnofficialOPCode();
}

void G6502::OPCode0x8C()
{
    // STY $nn
}

void G6502::OPCode0x8D()
{
    // STA $nn
}

void G6502::OPCode0x8E()
{
    // STX $nn
}

void G6502::OPCode0x8F()
{
    // UNOFFICIAL
    // SAX $nn
    UnofficialOPCode();
}

void G6502::OPCode0x90()
{
    // BCC $s
    OPcodes_Branch(!IsSetFlag(FLAG_CARRY));
}

void G6502::OPCode0x91()
{
    // STA ($n),Y
}

void G6502::OPCode0x92()
{
    // UNOFFICIAL
    // KILL
    UnofficialOPCode();
}

void G6502::OPCode0x93()
{
    // UNOFFICIAL
    // AHX ($n),Y
    UnofficialOPCode();
}

void G6502::OPCode0x94()
{
    // STY $n,X
}

void G6502::OPCode0x95()
{
    // STA $n,X
}

void G6502::OPCode0x96()
{
    // STX $n,Y
}

void G6502::OPCode0x97()
{
    // UNOFFICIAL
    // SAX $n,Y
    UnofficialOPCode();
}

void G6502::OPCode0x98()
{
    // TYA
}

void G6502::OPCode0x99()
{
    // STA $nn,Y
}

void G6502::OPCode0x9A()
{
    // TXS
}

void G6502::OPCode0x9B()
{
    // UNOFFICIAL
    // TAS $nn,Y
    UnofficialOPCode();
}

void G6502::OPCode0x9C()
{
    // SHY $nn,X
}

void G6502::OPCode0x9D()
{
    // STA $nn,X
}

void G6502::OPCode0x9E()
{
    // SHX $nn,Y
}

void G6502::OPCode0x9F()
{
    // UNOFFICIAL
    // AHX $nn,Y
    UnofficialOPCode();
}

void G6502::OPCode0xA0()
{
    // LDY #$n
    OPCodes_LD(&Y_, ImmediateAddressing());
}

void G6502::OPCode0xA1()
{
    // LDA $(nn,X)
    OPCodes_LD(&A_, Read(IndexedIndirectAddressing()));
}

void G6502::OPCode0xA2()
{
    // LDX #$n
    OPCodes_LD(&X_, ImmediateAddressing());
}

void G6502::OPCode0xA3()
{
    // UNOFFICIAL
    // LAX $(nn,X)
    UnofficialOPCode();
}

void G6502::OPCode0xA4()
{
    // LDY $n
    OPCodes_LD(&Y_, Read(ZeroPageAddressing()));
}

void G6502::OPCode0xA5()
{
    // LDA $n
    OPCodes_LD(&A_, Read(ZeroPageAddressing()));
}

void G6502::OPCode0xA6()
{
    // LDX $n
    OPCodes_LD(&X_, Read(ZeroPageAddressing()));
}

void G6502::OPCode0xA7()
{
    // UNOFFICIAL
    // LAX $n
    UnofficialOPCode();
}

void G6502::OPCode0xA8()
{
    // TAY
}

void G6502::OPCode0xA9()
{
    // LDA #$n
    OPCodes_LD(&A_, ImmediateAddressing());
}

void G6502::OPCode0xAA()
{
    // TAX
}

void G6502::OPCode0xAB()
{
    // UNOFFICIAL
    // LAX #$n
    UnofficialOPCode();
}

void G6502::OPCode0xAC()
{
    // LDY $nn
    OPCodes_LD(&Y_, Read(AbsoluteAddressing()));
}

void G6502::OPCode0xAD()
{
    // LDA $nn
    OPCodes_LD(&A_, Read(AbsoluteAddressing()));
}

void G6502::OPCode0xAE()
{
    // LDX $nn
    OPCodes_LD(&X_, Read(AbsoluteAddressing()));
}

void G6502::OPCode0xAF()
{
    // UNOFFICIAL
    // LAX $nn
    UnofficialOPCode();
}

void G6502::OPCode0xB0()
{
    // BCS $s
    OPcodes_Branch(IsSetFlag(FLAG_CARRY));
}

void G6502::OPCode0xB1()
{
    // LDA ($n),Y
    OPCodes_LD(&A_, Read(IndirectIndexedAddressing()));
}

void G6502::OPCode0xB2()
{
    // UNOFFICIAL
    // KILL
    UnofficialOPCode();
}

void G6502::OPCode0xB3()
{
    // UNOFFICIAL
    // LAX ($n),Y
    UnofficialOPCode();
}

void G6502::OPCode0xB4()
{
    // LDY $n,X
    OPCodes_LD(&Y_, Read(ZeroPageXAddressing()));
}

void G6502::OPCode0xB5()
{
    // LDA $n,X
    OPCodes_LD(&A_, Read(ZeroPageXAddressing()));
}

void G6502::OPCode0xB6()
{
    // LDX $n,Y
    OPCodes_LD(&X_, Read(ZeroPageYAddressing()));
}

void G6502::OPCode0xB7()
{
    // UNOFFICIAL
    // LAX $n,Y
    UnofficialOPCode();
}

void G6502::OPCode0xB8()
{
    // CLV
    OPCodes_ClearFlag(FLAG_OVERFLOW);
}

void G6502::OPCode0xB9()
{
    // LDA $nn,Y
    OPCodes_LD(&A_, Read(AbsoluteYAddressing()));
}

void G6502::OPCode0xBA()
{
    // TSX
}

void G6502::OPCode0xBB()
{
    // UNOFFICIAL
    // LAS $nn,Y
    UnofficialOPCode();
}

void G6502::OPCode0xBC()
{
    // LDY $nn,X
    OPCodes_LD(&Y_, Read(AbsoluteXAddressing()));
}

void G6502::OPCode0xBD()
{
    // LDA $nn,X
    OPCodes_LD(&A_, Read(AbsoluteXAddressing()));
}

void G6502::OPCode0xBE()
{
    // LDX $nn,Y
    OPCodes_LD(&X_, Read(AbsoluteYAddressing()));
}

void G6502::OPCode0xBF()
{
    // UNOFFICIAL
    // LAX $nn,Y
    UnofficialOPCode();
}

void G6502::OPCode0xC0()
{
    // CPY #$n
    OPCodes_CMP(&Y_, ImmediateAddressing());
}

void G6502::OPCode0xC1()
{
    // CMP $(nn,X)
    OPCodes_CMP(&A_, Read(IndexedIndirectAddressing()));
}

void G6502::OPCode0xC2()
{
    // UNOFFICIAL
    // NOP #$n
    UnofficialOPCode();
}

void G6502::OPCode0xC3()
{
    // UNOFFICIAL
    // DCP $(nn,X)
    UnofficialOPCode();
}

void G6502::OPCode0xC4()
{
    // CPY $n
    OPCodes_CMP(&Y_, Read(ZeroPageAddressing()));
}

void G6502::OPCode0xC5()
{
    // CMP $n
    OPCodes_CMP(&A_, Read(ZeroPageAddressing()));
}

void G6502::OPCode0xC6()
{
    // DEC $n
    OPCodes_DEC_Mem(ZeroPageAddressing());
}

void G6502::OPCode0xC7()
{
    // UNOFFICIAL
    // DCP $n
    UnofficialOPCode();
}

void G6502::OPCode0xC8()
{
    // INY
    OPCodes_INC_Reg(&Y_);
}

void G6502::OPCode0xC9()
{
    // CMP #$n
    OPCodes_CMP(&A_, ImmediateAddressing());
}

void G6502::OPCode0xCA()
{
    // DEX
    OPCodes_DEC_Reg(&X_);
}

void G6502::OPCode0xCB()
{
    // UNOFFICIAL
    // CMP #$n
    UnofficialOPCode();
}

void G6502::OPCode0xCC()
{
    // CPY $nn
    OPCodes_CMP(&Y_, Read(AbsoluteAddressing()));
}

void G6502::OPCode0xCD()
{
    // CMP $nn
    OPCodes_CMP(&A_, Read(AbsoluteAddressing()));
}

void G6502::OPCode0xCE()
{
    // DEC $nn
    OPCodes_DEC_Mem(AbsoluteAddressing());
}

void G6502::OPCode0xCF()
{
    // UNOFFICIAL
    // DCP $nn
    UnofficialOPCode();
}

void G6502::OPCode0xD0()
{
    // BNE $s
    OPcodes_Branch(!IsSetFlag(FLAG_ZERO));
}

void G6502::OPCode0xD1()
{
    // CMP ($n),Y
    OPCodes_CMP(&A_, Read(IndirectIndexedAddressing()));
}

void G6502::OPCode0xD2()
{
    // UNOFFICIAL
    // KILL
    UnofficialOPCode();
}

void G6502::OPCode0xD3()
{
    // UNOFFICIAL
    // DCP ($n),Y
    UnofficialOPCode();
}

void G6502::OPCode0xD4()
{
    // UNOFFICIAL
    // NOP $n,X
    UnofficialOPCode();
}

void G6502::OPCode0xD5()
{
    // CMP $n,X
    OPCodes_CMP(&A_, Read(ZeroPageXAddressing()));
}

void G6502::OPCode0xD6()
{
    // DEC $n,X
    OPCodes_DEC_Mem(ZeroPageXAddressing());
}

void G6502::OPCode0xD7()
{
    // UNOFFICIAL
    // DCP $n,X
    UnofficialOPCode();
}

void G6502::OPCode0xD8()
{
    // CLD
    OPCodes_ClearFlag(FLAG_DECIMAL);
}

void G6502::OPCode0xD9()
{
    // CMP $nn,Y
    OPCodes_CMP(&A_, Read(AbsoluteYAddressing()));
}

void G6502::OPCode0xDA()
{
    // UNOFFICIAL
    // NOP
    UnofficialOPCode();
}

void G6502::OPCode0xDB()
{
    // UNOFFICIAL
    // DCP $nn,Y
    UnofficialOPCode();
}

void G6502::OPCode0xDC()
{
    // UNOFFICIAL
    // NOP $nn,X
    UnofficialOPCode();
}

void G6502::OPCode0xDD()
{
    // CMP $nn,X
    OPCodes_CMP(&A_, Read(AbsoluteXAddressing()));
}

void G6502::OPCode0xDE()
{
    // DEC $nn,X
    OPCodes_DEC_Mem(AbsoluteXAddressing());
}

void G6502::OPCode0xDF()
{
    // UNOFFICIAL
    // DCP $nn,X
    UnofficialOPCode();
}

void G6502::OPCode0xE0()
{
    // CPX #$n
    OPCodes_CMP(&X_, ImmediateAddressing());
}

void G6502::OPCode0xE1()
{
    // SBC $(nn,X)
}

void G6502::OPCode0xE2()
{
    // UNOFFICIAL
    // NOP #$n
    UnofficialOPCode();
}

void G6502::OPCode0xE3()
{
    // UNOFFICIAL
    // ISC $(nn,X)
    UnofficialOPCode();
}

void G6502::OPCode0xE4()
{
    // CPX $n
    OPCodes_CMP(&X_, Read(ZeroPageAddressing()));
}

void G6502::OPCode0xE5()
{
    // SBC $n
}

void G6502::OPCode0xE6()
{
    // INC $n
    OPCodes_INC_Mem(ZeroPageAddressing());
}

void G6502::OPCode0xE7()
{
    // UNOFFICIAL
    // ISC $n
    UnofficialOPCode();
}

void G6502::OPCode0xE8()
{
    // INX
    OPCodes_INC_Reg(&X_);
}

void G6502::OPCode0xE9()
{
    // SBC #$n
}

void G6502::OPCode0xEA()
{
    // NOP
}

void G6502::OPCode0xEB()
{
    // UNOFFICIAL
    // SBC #$n
    UnofficialOPCode();
}

void G6502::OPCode0xEC()
{
    // CPX $nn
    OPCodes_CMP(&X_, Read(AbsoluteAddressing()));
}

void G6502::OPCode0xED()
{
    // SBC $nn
}

void G6502::OPCode0xEE()
{
    // INC $nn
    OPCodes_INC_Mem(AbsoluteAddressing());
}

void G6502::OPCode0xEF()
{
    // UNOFFICIAL
    // ISC $nn
    UnofficialOPCode();
}

void G6502::OPCode0xF0()
{
    // BEQ $s
    OPcodes_Branch(IsSetFlag(FLAG_ZERO));
}

void G6502::OPCode0xF1()
{
    // SBC ($n),Y
}

void G6502::OPCode0xF2()
{
    // UNOFFICIAL
    // KILL
    UnofficialOPCode();
}

void G6502::OPCode0xF3()
{
    // UNOFFICIAL
    // ISC ($n),Y
    UnofficialOPCode();
}

void G6502::OPCode0xF4()
{
    // UNOFFICIAL
    // NOP $n,X
    UnofficialOPCode();
}

void G6502::OPCode0xF5()
{
    // SBC $n,X
}

void G6502::OPCode0xF6()
{
    // INC $n,X
    OPCodes_INC_Mem(ZeroPageXAddressing());
}

void G6502::OPCode0xF7()
{
    // UNOFFICIAL
    // ISC $n,X
    UnofficialOPCode();
}

void G6502::OPCode0xF8()
{
    // SED
    OPCodes_SetFlag(FLAG_DECIMAL);
}

void G6502::OPCode0xF9()
{
    // SBC $nn,Y
}

void G6502::OPCode0xFA()
{
    // UNOFFICIAL
    // NOP
    UnofficialOPCode();
}

void G6502::OPCode0xFB()
{
    // UNOFFICIAL
    // ISC $nn,Y
    UnofficialOPCode();
}

void G6502::OPCode0xFC()
{
    // UNOFFICIAL
    // NOP $nn,X
    UnofficialOPCode();
}

void G6502::OPCode0xFD()
{
    // SBC $nn,X
}

void G6502::OPCode0xFE()
{
    // INC $nn,X
    OPCodes_INC_Mem(AbsoluteXAddressing());
}

void G6502::OPCode0xFF()
{
    // UNOFFICIAL
    // ISC $nn,X
    UnofficialOPCode();
}

} // namespace g6502
