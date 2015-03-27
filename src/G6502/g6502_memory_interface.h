#ifndef G6502_MEMORYINTERFACE_H_
#define	G6502_MEMORYINTERFACE_H_

#include "g6502_definitions.h"

namespace g6502
{
    
class MemoryInterface
{
public:
    MemoryInterface() {}
    virtual ~MemoryInterface() {}
    virtual u8 Read(u16 address) = 0;
    virtual void Write(u16 address, u8 value) = 0;
    virtual u8 Retrieve(u16 address) = 0;
    virtual void Load(u16 address, u8 value) = 0;
    virtual void Disassemble(u16 address, const char* disassembled_string) = 0;
    virtual bool IsDisassembled(u16 address) = 0;
};

} // namespace g6502

#endif // G6502_MEMORYINTERFACE_H_

