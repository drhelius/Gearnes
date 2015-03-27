/*
 * GZ80 - Zilog Z80 Emulator
 * Copyright (C) 2014  Ignacio Sanchez Gines

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

#ifndef G6502_CORE_H_
#define	G6502_CORE_H_

#include "g6502_definitions.h"
#include "g6502_eight_bit_register.h"
#include "g6502_sixteen_bit_register.h"
#include "g6502_memory_interface.h"

namespace g6502
{
   
class G6502
{
public:
    G6502();
    ~G6502();
    void Init();
    void Reset();
    unsigned int RunFor(unsigned int t_states);
    unsigned int Tick();
    void RequestIRQ(bool assert);
    void RequestNMI();
    void SetMemoryImpl(MemoryInterface* memory_impl);

private:
    typedef void (G6502::*OPCptr) (void);
    OPCptr opcodes_[256];
    SixteenBitRegister PC_;
    EightBitRegister A_;
    EightBitRegister X_;
    EightBitRegister Y_;
    EightBitRegister S_;
    EightBitRegister P_;
    unsigned int t_states_;
    bool interrupt_asserted_;
    bool nmi_interrupt_requested_;
    MemoryInterface* memory_impl_;

private:
    u8 Fetch8();
    u16 Fetch16();
    void ClearAllFlags();
    void SetZeroFlagFromResult(u8 result);
    void SetNegativeFlagFromResult(u8 result);
    void SetFlag(u8 flag);
    void FlipFlag(u8 flag);
    void ClearFlag(u8 flag);
    bool IsSetFlag(u8 flag);
    void StackPush(SixteenBitRegister* reg);
    void StackPop(SixteenBitRegister* reg);
    void StackPush(EightBitRegister* reg);
    void StackPop(EightBitRegister* reg);
    u8 ImmediateAddressing();
    u8 ZeroPageAddressing();
    u8 ZeroPageXAddressing();
    u8 ZeroPageYddressing();
    s8 RelativeAddressing();
    u16 AbsoluteAddressing();
    u16 AbsoluteXAddressing();
    u16 AbsoluteYAddressing();
    u16 IndirectAddressing();
    u8 IndexedIndirectAddressing();
    u8 IndirectIndexedAddressing();
    void UnofficialOPCode();
    /*
    void OPCodes_LD(EightBitRegister* reg1, u8 value);
    void OPCodes_LD(EightBitRegister* reg, u16 address);
    void OPCodes_LD(u16 address, u8 reg);
    void OPCodes_LD_dd_nn(SixteenBitRegister* reg);
    void OPCodes_LD_nn_dd(SixteenBitRegister* reg);
    void OPCodes_LDI();
    void OPCodes_LDD();
    void OPCodes_RST(u16 address);
    void OPCodes_CALL_nn();
    void OPCodes_CALL_nn_Conditional(bool condition);
    void OPCodes_JP_nn();
    void OPCodes_JP_nn_Conditional(bool condition);
    void OPCodes_JR_n();
    void OPCodes_JR_n_conditional(bool condition);
    void OPCodes_RET();
    void OPCodes_RET_Conditional(bool condition);
    void OPCodes_IN_C(EightBitRegister* reg);
    void OPCodes_INI();
    void OPCodes_IND();
    void OPCodes_OUT_C(EightBitRegister* reg);
    void OPCodes_OUTI();
    void OPCodes_OUTD();
    void OPCodes_EX(SixteenBitRegister* reg1, SixteenBitRegister* reg2);
    void OPCodes_OR(u8 number);
    void OPCodes_XOR(u8 number);
    void OPCodes_AND(u8 number);
    void OPCodes_CP(u8 number);
    void OPCodes_CPI();
    void OPCodes_CPD();
    void OPCodes_INC(EightBitRegister* reg);
    void OPCodes_INC_HL();
    void OPCodes_DEC(EightBitRegister* reg);
    void OPCodes_DEC_HL();
    void OPCodes_ADD(u8 number);
    void OPCodes_ADC(u8 number);
    void OPCodes_SUB(u8 number);
    void OPCodes_SBC(u8 number);
    void OPCodes_ADD_HL(u16 number);
    void OPCodes_ADC_HL(u16 number);
    void OPCodes_SBC_HL(u16 number);
    void OPCodes_SLL(EightBitRegister* reg);
    void OPCodes_SLL_HL();
    void OPCodes_SLA(EightBitRegister* reg);
    void OPCodes_SLA_HL();
    void OPCodes_SRA(EightBitRegister* reg);
    void OPCodes_SRA_HL();
    void OPCodes_SRL(EightBitRegister* reg);
    void OPCodes_SRL_HL();
    void OPCodes_RLC(EightBitRegister* reg, bool register_A = false);
    void OPCodes_RLC_HL();
    void OPCodes_RL(EightBitRegister* reg, bool register_A = false);
    void OPCodes_RL_HL();
    void OPCodes_RRC(EightBitRegister* reg, bool register_A = false);
    void OPCodes_RRC_HL();
    void OPCodes_RR(EightBitRegister* reg, bool register_A = false);
    void OPCodes_RR_HL();
    void OPCodes_BIT(EightBitRegister* reg, int bit);
    void OPCodes_BIT_HL(int bit);
    void OPCodes_SET(EightBitRegister* reg, int bit);
    void OPCodes_SET_HL(int bit);
    void OPCodes_RES(EightBitRegister* reg, int bit);
    void OPCodes_RES_HL(int bit);
    */
    void InitOPCodeFunctors();

    void OPCode0x00(); void OPCode0x01(); void OPCode0x02(); void OPCode0x03();
    void OPCode0x04(); void OPCode0x05(); void OPCode0x06(); void OPCode0x07();
    void OPCode0x08(); void OPCode0x09(); void OPCode0x0A(); void OPCode0x0B();
    void OPCode0x0C(); void OPCode0x0D(); void OPCode0x0E(); void OPCode0x0F();
    void OPCode0x10(); void OPCode0x11(); void OPCode0x12(); void OPCode0x13();
    void OPCode0x14(); void OPCode0x15(); void OPCode0x16(); void OPCode0x17();
    void OPCode0x18(); void OPCode0x19(); void OPCode0x1A(); void OPCode0x1B();
    void OPCode0x1C(); void OPCode0x1D(); void OPCode0x1E(); void OPCode0x1F();
    void OPCode0x20(); void OPCode0x21(); void OPCode0x22(); void OPCode0x23();
    void OPCode0x24(); void OPCode0x25(); void OPCode0x26(); void OPCode0x27();
    void OPCode0x28(); void OPCode0x29(); void OPCode0x2A(); void OPCode0x2B();
    void OPCode0x2C(); void OPCode0x2D(); void OPCode0x2E(); void OPCode0x2F();
    void OPCode0x30(); void OPCode0x31(); void OPCode0x32(); void OPCode0x33();
    void OPCode0x34(); void OPCode0x35(); void OPCode0x36(); void OPCode0x37();
    void OPCode0x38(); void OPCode0x39(); void OPCode0x3A(); void OPCode0x3B();
    void OPCode0x3C(); void OPCode0x3D(); void OPCode0x3E(); void OPCode0x3F();
    void OPCode0x40(); void OPCode0x41(); void OPCode0x42(); void OPCode0x43();
    void OPCode0x44(); void OPCode0x45(); void OPCode0x46(); void OPCode0x47();
    void OPCode0x48(); void OPCode0x49(); void OPCode0x4A(); void OPCode0x4B();
    void OPCode0x4C(); void OPCode0x4D(); void OPCode0x4E(); void OPCode0x4F();
    void OPCode0x50(); void OPCode0x51(); void OPCode0x52(); void OPCode0x53();
    void OPCode0x54(); void OPCode0x55(); void OPCode0x56(); void OPCode0x57();
    void OPCode0x58(); void OPCode0x59(); void OPCode0x5A(); void OPCode0x5B();
    void OPCode0x5C(); void OPCode0x5D(); void OPCode0x5E(); void OPCode0x5F();
    void OPCode0x60(); void OPCode0x61(); void OPCode0x62(); void OPCode0x63();
    void OPCode0x64(); void OPCode0x65(); void OPCode0x66(); void OPCode0x67();
    void OPCode0x68(); void OPCode0x69(); void OPCode0x6A(); void OPCode0x6B();
    void OPCode0x6C(); void OPCode0x6D(); void OPCode0x6E(); void OPCode0x6F();
    void OPCode0x70(); void OPCode0x71(); void OPCode0x72(); void OPCode0x73();
    void OPCode0x74(); void OPCode0x75(); void OPCode0x76(); void OPCode0x77();
    void OPCode0x78(); void OPCode0x79(); void OPCode0x7A(); void OPCode0x7B();
    void OPCode0x7C(); void OPCode0x7D(); void OPCode0x7E(); void OPCode0x7F();
    void OPCode0x80(); void OPCode0x81(); void OPCode0x82(); void OPCode0x83();
    void OPCode0x84(); void OPCode0x85(); void OPCode0x86(); void OPCode0x87();
    void OPCode0x88(); void OPCode0x89(); void OPCode0x8A(); void OPCode0x8B();
    void OPCode0x8C(); void OPCode0x8D(); void OPCode0x8E(); void OPCode0x8F();
    void OPCode0x90(); void OPCode0x91(); void OPCode0x92(); void OPCode0x93();
    void OPCode0x94(); void OPCode0x95(); void OPCode0x96(); void OPCode0x97();
    void OPCode0x98(); void OPCode0x99(); void OPCode0x9A(); void OPCode0x9B();
    void OPCode0x9C(); void OPCode0x9D(); void OPCode0x9E(); void OPCode0x9F();
    void OPCode0xA0(); void OPCode0xA1(); void OPCode0xA2(); void OPCode0xA3();
    void OPCode0xA4(); void OPCode0xA5(); void OPCode0xA6(); void OPCode0xA7();
    void OPCode0xA8(); void OPCode0xA9(); void OPCode0xAA(); void OPCode0xAB();
    void OPCode0xAC(); void OPCode0xAD(); void OPCode0xAE(); void OPCode0xAF();
    void OPCode0xB0(); void OPCode0xB1(); void OPCode0xB2(); void OPCode0xB3();
    void OPCode0xB4(); void OPCode0xB5(); void OPCode0xB6(); void OPCode0xB7();
    void OPCode0xB8(); void OPCode0xB9(); void OPCode0xBA(); void OPCode0xBB();
    void OPCode0xBC(); void OPCode0xBD(); void OPCode0xBE(); void OPCode0xBF();
    void OPCode0xC0(); void OPCode0xC1(); void OPCode0xC2(); void OPCode0xC3();
    void OPCode0xC4(); void OPCode0xC5(); void OPCode0xC6(); void OPCode0xC7();
    void OPCode0xC8(); void OPCode0xC9(); void OPCode0xCA(); void OPCode0xCB();
    void OPCode0xCC(); void OPCode0xCD(); void OPCode0xCE(); void OPCode0xCF();
    void OPCode0xD0(); void OPCode0xD1(); void OPCode0xD2(); void OPCode0xD3();
    void OPCode0xD4(); void OPCode0xD5(); void OPCode0xD6(); void OPCode0xD7();
    void OPCode0xD8(); void OPCode0xD9(); void OPCode0xDA(); void OPCode0xDB();
    void OPCode0xDC(); void OPCode0xDD(); void OPCode0xDE(); void OPCode0xDF();
    void OPCode0xE0(); void OPCode0xE1(); void OPCode0xE2(); void OPCode0xE3();
    void OPCode0xE4(); void OPCode0xE5(); void OPCode0xE6(); void OPCode0xE7();
    void OPCode0xE8(); void OPCode0xE9(); void OPCode0xEA(); void OPCode0xEB();
    void OPCode0xEC(); void OPCode0xED(); void OPCode0xEE(); void OPCode0xEF();
    void OPCode0xF0(); void OPCode0xF1(); void OPCode0xF2(); void OPCode0xF3();
    void OPCode0xF4(); void OPCode0xF5(); void OPCode0xF6(); void OPCode0xF7();
    void OPCode0xF8(); void OPCode0xF9(); void OPCode0xFA(); void OPCode0xFB();
    void OPCode0xFC(); void OPCode0xFD(); void OPCode0xFE(); void OPCode0xFF();
};

} // namespace g6502

#include "g6502_core_inl.h"

#endif // G6502_CORE_H_

