#include "decoder.hpp"
#include "state.h"
#include "isa_exe.hpp"
#include "aux.hpp"
#include <cstdlib>
#include <stdio.h>

#define PC_incr state->SetPc(state->GetPc() + 4)

void ADDIExec   (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) + static_cast<int32_t>(instr->GetImm())); 
    PC_incr;
}

void SLTIExec   (const Instruction* instr, State* state)
{
    (int32_t)state->GetReg(instr->GetRs1()) < (int32_t)instr->GetImm() ? state->SetReg(instr->GetRd(), 1) : state->SetReg(instr->GetRd(), 0);
    PC_incr;
}

void SLTIUExec  (const Instruction* instr, State* state)
{
    state->GetReg(instr->GetRs1()) < instr->GetImm() ? state->SetReg(instr->GetRd(), 1) : state->SetReg(instr->GetRd(), 0);
    PC_incr;
}

void XORIExec   (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) ^ instr->GetImm());
    PC_incr;
}

void ORIExec    (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) | instr->GetImm());
    PC_incr;
}

void ANDIExec   (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) & instr->GetImm());
    PC_incr;
}

void SBExec     (const Instruction* instr, State* state)
{
    state->WriteByte (instr->GetImm() + static_cast<int32_t>(state->GetReg(instr->GetRs1())), state->GetReg(instr->GetRs2()));
    PC_incr;
}

void SHExec     (const Instruction* instr, State* state)
{
    state->WriteHalfWord (instr->GetImm() + static_cast<int32_t>(state->GetReg(instr->GetRs1()), state->GetReg(instr->GetRs2())));
    PC_incr;
}

void SWExec     (const Instruction* instr, State* state)
{
    state->WriteWord (instr->GetImm() + static_cast<int32_t>(state->GetReg(instr->GetRs1())), state->GetReg(instr->GetRs2()));
    PC_incr;
}

void LBExec     (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), static_cast<int32_t>(static_cast<int8_t>(state->ReadByte (instr->GetImm() + state->GetReg(instr->GetRs1())))));
    PC_incr;
}

void LHExec     (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), static_cast<int32_t>(static_cast<int16_t>(state->ReadHalfWord (instr->GetImm() + state->GetReg(instr->GetRs1())))));
    PC_incr;
}

void LWExec     (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), static_cast<int32_t>(state->ReadWord (instr->GetImm() + state->GetReg(instr->GetRs1()))));
    PC_incr;
}

void LBUExec    (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), static_cast <uint32_t>(state->ReadByte (instr->GetImm() + state->GetReg(instr->GetRs1()))));
    PC_incr;
}

void LHUExec    (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), static_cast <uint32_t>(state->ReadHalfWord (instr->GetImm() + state->GetReg(instr->GetRs1()))));
    PC_incr;
}


void LUIExec    (const Instruction* instr, State* state)
{
    state->SetReg (instr->GetRd(), (instr->GetImm()) << 12);
    PC_incr;
}

void AUIPCExec  (const Instruction* instr, State* state)
{
    state->SetReg (instr->GetRd(), (instr->GetImm() << 12) + state->GetPc());
    PC_incr;
}

void BEQExec    (const Instruction* instr, State* state)
{
    state->GetReg(instr->GetRs1()) == state->GetReg(instr->GetRs2()) ? 
    state->SetPc(state->GetPc() + (instr->GetImm() << 1)) : state->SetPc(state->GetPc() + 4); 
}

void BNEExec    (const Instruction* instr, State* state)
{
    state->GetReg(instr->GetRs1()) != state->GetReg(instr->GetRs2()) ?
    state->SetPc(state->GetPc() + (instr->GetImm() << 1)) : state->SetPc(state->GetPc() + 4); 
}

void BLTExec    (const Instruction* instr, State* state)
{
    static_cast<int32_t>(state->GetReg(instr->GetRs1())) < static_cast<int32_t>(state->GetReg(instr->GetRs2())) ?
    state->SetPc(state->GetPc() + (instr->GetImm() << 1)) : state->SetPc(state->GetPc() + 4); 
}

void BGEExec    (const Instruction* instr, State* state)
{
    static_cast<int32_t>(state->GetReg(instr->GetRs1())) >= static_cast<int32_t>(state->GetReg(instr->GetRs2())) ? 
    state->SetPc(state->GetPc() + (static_cast<int32_t>(instr->GetImm()) << 1)) : state->SetPc(state->GetPc() + 4); 
}

void BLTUExec   (const Instruction* instr, State* state)
{
    state->GetReg(instr->GetRs1()) < state->GetReg(instr->GetRs2()) ? 
    state->SetPc(state->GetPc() + (instr->GetImm() << 1)) : state->SetPc(state->GetPc() + 4); 
}

void BGEUExec   (const Instruction* instr, State* state)
{
    state->GetReg(instr->GetRs1()) > state->GetReg(instr->GetRs2()) ?
    state->SetPc(state->GetPc() + (instr->GetImm() << 1)) : state->SetPc(state->GetPc() + 4); 
}

void JALExec    (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), state->GetPc() + 4);
    state->SetPc(state->GetPc() + (static_cast<int32_t>(instr->GetImm()) << 1));
}

void JALRExec   (const Instruction* instr, State* state)
{
   state->SetReg(instr->GetRd(), state->GetPc() + 4);
   state->SetPc(state->GetPc() + ((instr->GetRs1() + static_cast<int32_t>(instr->GetImm())) & 0xFFFFFFFE));  
   if (instr->GetOppcode() == 0b1100111 && instr->GetRs1() == 1 && instr->GetRd() == 0)
       throw HartException("Jumping to return address!\n");
}

void SLLIExec   (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), instr->GetRs1() << (instr->GetImm() & 0b11111));
    PC_incr;
}

void SRLIExec   (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), instr->GetRs1() >> (instr->GetImm() & 0b11111));
    PC_incr;
}

void SRAIExec   (const Instruction* instr, State* state)
{
    uint32_t sb_copy = static_cast<int32_t>(instr->GetImm()) < 0 ? ~(~0u >> instr->GetImm()) : 0;
    state->SetReg(instr->GetRd(), (state->GetReg(instr->GetRs1()) >> instr->GetImm()) | sb_copy);
    PC_incr;
}

void ADDExec   (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) + state->GetReg(instr->GetRs2()));
    PC_incr;
}

void SUBExec    (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) - state->GetReg(instr->GetRs2()));
    PC_incr;
}

void SLLExec    (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) << state->GetReg(instr->GetRs2()));
    PC_incr;
}

void SLTExec    (const Instruction* instr, State* state)
{
    static_cast<int32_t>(state->GetReg(instr->GetRs1())) < static_cast<int32_t>(state->GetReg(instr->GetRs2())) ? 
    state->SetReg(instr->GetRd(), 1):
    state->SetReg(instr->GetRd(), 0);
    PC_incr;
}

void SLTUExec   (const Instruction* instr, State* state)
{
    state->GetReg(instr->GetRs1()) < state->GetReg(instr->GetRs2()) ? 
    state->SetReg(instr->GetRd(), 1):
    state->SetReg(instr->GetRd(), 0);
    PC_incr;
}

void XORExec    (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) ^ state->GetReg(instr->GetRs2()));
    PC_incr;
}

void SRLExec    (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) >> (state->GetReg(instr->GetRs2()) & 0b11111));
    PC_incr;
}

void SRAExec    (const Instruction* instr, State* state)
{
    uint8_t offs = state->GetReg(instr->GetRs2()) & 0b11111;
    uint32_t sb_copy = static_cast<int8_t>(instr->GetRs1()) < 0 ? ~(~0xFFFFFFFF >> offs) : 0; 
    state->SetReg(instr->GetRd(), (state->GetReg(instr->GetRs1()) >> offs) | sb_copy);
    PC_incr;
}

void ORExec     (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) | state->GetReg(instr->GetRs2()));
    PC_incr;
}

void ANDExec    (const Instruction* instr, State* state)
{
    state->SetReg(instr->GetRd(), state->GetReg(instr->GetRs1()) & state->GetReg(instr->GetRs2()));
    PC_incr;
}

void DUMMYExec  (const Instruction* instr, State* state)
{
    printf ("DUMMY instruction\n");
}

void ECALLExec  (const Instruction* instr, State* state)
{
    throw HartException ("Finished execution!\n");
}
