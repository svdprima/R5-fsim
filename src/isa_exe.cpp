#include "decoder.hpp"
#include "hart_state.h"
#include "isa_exe.hpp"
#include "aux.hpp"
#include <cstdlib>
#include <stdio.h>

#define PC_incr hart_state->SetPc(GET_PC() + 4)
#define RDn instr->GetRd()
#define RDv  (hart_state->GetReg(instr->GetRd()))
#define RS1n instr->GetRs1()
#define RS1v (hart_state->GetReg(instr->GetRs1()))
#define RS2n instr->GetRs2()
#define RS2v (hart_state->GetReg(instr->GetRs2()))
#define SET_PC(x) (hart_state->SetPc(x))
#define GET_PC()  (hart_state->GetPc())
#define SET_R(x, val) (hart_state->SetReg(x, val))
#define GET_R(x) (hart_state->GetReg(x));
#define IMM instr->GetImm()

void ADDIExec   (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v + static_cast<int32_t>(IMM)); 
    PC_incr;
}

void SLTIExec   (const Instruction* instr, HartState* hart_state)
{
    (int32_t)RS1v < (int32_t)IMM ? SET_R(RDn, 1) : SET_R(RDn, 0);
    PC_incr;
}

void SLTIUExec  (const Instruction* instr, HartState* hart_state)
{
    RS1v < IMM ? SET_R(RDn, 1) : SET_R(RDn, 0);
    PC_incr;
}

void XORIExec   (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v ^ IMM);
    PC_incr;
}

void ORIExec    (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v | IMM);
    PC_incr;
}

void ANDIExec   (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v & IMM);
    PC_incr;
}

void SBExec     (const Instruction* instr, HartState* hart_state)
{
    hart_state->WriteByte (IMM + static_cast<int32_t>(RS1v), RS2v);
    PC_incr;
}

void SHExec     (const Instruction* instr, HartState* hart_state)
{
    hart_state->WriteHalfWord (IMM + static_cast<int32_t>(RS1v), RS2v);
    PC_incr;
}

void SWExec     (const Instruction* instr, HartState* hart_state)
{
    hart_state->WriteWord (IMM + static_cast<int32_t>(RS1v), RS2v);
    PC_incr;
}

void LBExec     (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, static_cast<int32_t>(static_cast<int8_t>(hart_state->ReadByte (IMM + RS1v))));
    PC_incr;
}

void LHExec     (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, static_cast<int32_t>(static_cast<int16_t>(hart_state->ReadHalfWord (IMM + RS1v))));
    PC_incr;
}

void LWExec     (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, static_cast<int32_t>(hart_state->ReadWord (IMM + RS1v)));
    PC_incr;
}

void LBUExec    (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, static_cast <uint32_t>(hart_state->ReadByte (IMM + RS1v)));
    PC_incr;
}

void LHUExec    (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, static_cast <uint32_t>(hart_state->ReadHalfWord (IMM + RS1v)));
    PC_incr;
}


void LUIExec    (const Instruction* instr, HartState* hart_state)
{
    SET_R (RDn, (IMM) << 12);
    PC_incr;
}

void AUIPCExec  (const Instruction* instr, HartState* hart_state)
{
    SET_R (RDn, (IMM << 12) + GET_PC());
    PC_incr;
}

void BEQExec    (const Instruction* instr, HartState* hart_state)
{
    RS1v == RS2v ? 
    SET_PC(GET_PC() + (IMM << 1)) : SET_PC(GET_PC() + 4); 
}

void BNEExec    (const Instruction* instr, HartState* hart_state)
{
    RS1v != RS2v ?
    SET_PC(GET_PC() + (IMM << 1)) : SET_PC(GET_PC() + 4); 
}

void BLTExec    (const Instruction* instr, HartState* hart_state)
{
    static_cast<int32_t>(RS1v) < static_cast<int32_t>(RS2v) ?
    SET_PC(GET_PC() + (IMM << 1)) : SET_PC(GET_PC() + 4); 
}

void BGEExec    (const Instruction* instr, HartState* hart_state)
{
    static_cast<int32_t>(RS1v) >= static_cast<int32_t>(RS2v) ? 
    hart_state->SetPc(GET_PC() + (static_cast<int32_t>(IMM) << 1)) : SET_PC(GET_PC() + 4); 
}

void BLTUExec   (const Instruction* instr, HartState* hart_state)
{
    RS1v < RS2v ? 
    hart_state->SetPc(GET_PC() + (IMM << 1)) : SET_PC(GET_PC() + 4); 
}

void BGEUExec   (const Instruction* instr, HartState* hart_state)
{
    RS1v > RS2v ?
    hart_state->SetPc(GET_PC() + (IMM << 1)) : SET_PC(GET_PC() + 4); 
}

void JALExec    (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, GET_PC() + 4);
    SET_PC(GET_PC() + (static_cast<int32_t>(IMM) << 1));
}

void JALRExec   (const Instruction* instr, HartState* hart_state)
{
   SET_R(RDn, GET_PC() + 4);
   SET_PC((RS1v + IMM) & 0xFFFFFFFE);  
}

void SLLIExec   (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v << (IMM & 0b11111));
    PC_incr;
}

void SRLIExec   (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v >> (IMM & 0b11111));
    PC_incr;
}

void SRAIExec   (const Instruction* instr, HartState* hart_state)
{
    uint32_t sb_copy = static_cast<int32_t>(IMM) < 0 ? ~(~0u >> instr->GetImm()) : 0;
    SET_R(RDn, (RS1v >> IMM) | sb_copy);
    PC_incr;
}

void ADDExec   (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v + RS2v);
    PC_incr;
}

void SUBExec    (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v - RS2v);
    PC_incr;
}

void SLLExec    (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v << RS2v);
    PC_incr;
}

void SLTExec    (const Instruction* instr, HartState* hart_state)
{
    static_cast<int32_t>(RS1v) < static_cast<int32_t>(RS2v) ? 
    SET_R(RDn, 1):
    SET_R(RDn, 0);
    PC_incr;
}

void SLTUExec   (const Instruction* instr, HartState* hart_state)
{
    RS1v < RS2v ? 
    SET_R(RDn, 1):
    SET_R(RDn, 0);
    PC_incr;
}

void XORExec    (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v ^ RS2v);
    PC_incr;
}

void SRLExec    (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v >> (RS2v & 0b11111));
    PC_incr;
}

void SRAExec    (const Instruction* instr, HartState* hart_state)
{
    uint8_t offs = RS2v & 0b11111;
    uint32_t sb_copy = static_cast<int8_t>(RS1v) < 0 ? ~(~0xFFFFFFFF >> offs) : 0; 
    SET_R(RDn, (RS1v >> offs) | sb_copy);
    PC_incr;
}

void ORExec     (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v | RS2v);
    PC_incr;
}

void ANDExec    (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v & RS2v);
    PC_incr;
}

void DUMMYExec  (const Instruction* instr, HartState* hart_state)
{
    printf ("DUMMY instruction\n");
}

void ECALLExec  (const Instruction* instr, HartState* hart_state)
{
    throw HartException ("Finished execution!\n");
}

void MULExec    (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS1v * RS2v);    
    PC_incr;
}

void MULHExec   (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, ((static_cast<int64_t>(RS1v)*static_cast<int64_t>(RS2v))) >> 32);
    PC_incr;
}

void MULHSUExec (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, ((static_cast<int64_t>(RS1v)*static_cast<uint64_t>RS2v)) >> 32);
    PC_incr;
}

void MULHUExec  (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, (static_cast<uint64_t>RS1v * static_cast<uint64_t>RS2v) >> 32);
    PC_incr;
}

void DIVExec    (const Instruction* instr, HartState* hart_state)
{
    if (RS2v == 0)
        throw HartException("Division by zero!\n");
    SET_R(RDn, static_cast<int32_t>(RS1v) / static_cast<int32_t>(RS2v));
    PC_incr;
}

void DIVUExec   (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS2v ? RS1v / RS2v : UINT32_MAX);
    PC_incr;
}

void REMExec    (const Instruction* instr, HartState* hart_state)
{
    if (RS2v == 0)
        SET_R(RDn, RS1v);
    SET_R(RDn, static_cast<int32_t>(RS1v) % static_cast<int32_t>(RS2v));
    PC_incr;
}

void REMUExec   (const Instruction* instr, HartState* hart_state)
{
    SET_R(RDn, RS2v? RS1v % RS2v : RS1v);
    PC_incr;
}
