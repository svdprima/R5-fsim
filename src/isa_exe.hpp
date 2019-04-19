#ifndef ISA_EXE_HPP
#define ISA_EXE_HPP

#include <cstdlib>
#include <stdio.h>
#include "hart_state.h"
#include "ir.hpp"
#include "aux.hpp"

#define PC_incr hart_state->SetPc(GET_PC() + 4)
#define RDn cur_instr->GetRd()
#define sRDn cur_instr->GetRd_2()
#define tRDn cur_instr->GetRd_3()
#define RDv  (hart_state->GetReg(cur_instr->GetRd()))
#define RS1n cur_instr->GetRs1()
#define RS1v (hart_state->GetReg(cur_instr->GetRs1()))
#define sRS1v (hart_state->GetReg(cur_instr->GetRs1_2()))
#define tRS1v (hart_state->GetReg(cur_instr->GetRs1_3()))
#define RS2n cur_instr->GetRs2()
#define RS2v (hart_state->GetReg(cur_instr->GetRs2()))
#define sRS2v (hart_state->GetReg(cur_instr->GetRs2_2()))
#define tRS2v (hart_state->GetReg(cur_instr->GetRs2_3()))
#define SET_PC(x) (hart_state->SetPc(x))
#define GET_PC()  (hart_state->GetPc())
#define SET_R(x, val) (hart_state->SetReg(x, val))
#define GET_R(x) (hart_state->GetReg(x));
#define IMM cur_instr->GetImm()
#define sIMM cur_instr->GetImm_2()
#define tIMM cur_instr->GetImm_3()
#define NEXT_INSTR \
{ \
    (cur_instr + 1)->ExecCommand(first_instr, hart_state); \
}
#define NEXT_2_INSTR \
{ \
    (cur_instr + 2)->ExecCommand(first_instr, hart_state); \
}
#define NEXT_3_INSTR \
{ \
    (cur_instr + 3)->ExecCommand(first_instr, hart_state); \
}
#define GET_SATP() hart_state->GetSatp()
#define SET_SATP(x) hart_state->SetSatp(x)
#define PRINT_SATP hart_state->PrintSatp()
#define CMD_incr(x) hart_state->IncreaseCmdCount(x)

void ADDIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v + static_cast<int32_t>(IMM)); 
    NEXT_INSTR;
}

void SLTIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    (int32_t)RS1v < (int32_t)IMM ? SET_R(RDn, 1) : SET_R(RDn, 0);
    NEXT_INSTR;
}

void SLTIUExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    RS1v < IMM ? SET_R(RDn, 1) : SET_R(RDn, 0);
    NEXT_INSTR;
}

void XORIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v ^ IMM);
    NEXT_INSTR;
}

void ORIExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v | IMM);
    NEXT_INSTR;
}

void ANDIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v & IMM);
    NEXT_INSTR;
}

void SBExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    hart_state->WriteByte (IMM + static_cast<int32_t>(RS1v), RS2v);
    NEXT_INSTR;
}

void SHExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    hart_state->WriteHalfWord (IMM + static_cast<int32_t>(RS1v), RS2v);
    NEXT_INSTR;
}

void SWExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    hart_state->WriteWord (IMM + static_cast<int32_t>(RS1v), RS2v);
    NEXT_INSTR;
}

void LBExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, static_cast<int32_t>(static_cast<int8_t>(hart_state->ReadByte (IMM + RS1v))));
    NEXT_INSTR;
}

void LHExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, static_cast<int32_t>(static_cast<int16_t>(hart_state->ReadHalfWord (IMM + RS1v))));
    NEXT_INSTR;
}

void LWExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, static_cast<int32_t>(hart_state->ReadWord (IMM + RS1v)));
    NEXT_INSTR;
}

void LBUExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, static_cast <uint32_t>(hart_state->ReadByte (IMM + RS1v)));
    NEXT_INSTR;
}

void LHUExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, static_cast <uint32_t>(hart_state->ReadHalfWord (IMM + RS1v)));
    NEXT_INSTR;
}


void LUIExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R (RDn, (IMM) << 12);
    NEXT_INSTR;
}

void AUIPCExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R (RDn, (IMM << 12) + GET_PC());
    NEXT_INSTR;
}

void BEQExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    RS1v == RS2v ?
    SET_PC(GET_PC() + (cur_instr - first_instr) * 4 + (IMM << 1)) : 
    SET_PC(GET_PC() + (cur_instr - first_instr + 1) * 4); 
    CMD_incr(cur_instr - first_instr + 1);
}

void BNEExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    RS1v != RS2v ?
    SET_PC(GET_PC() + (cur_instr - first_instr) * 4 + (IMM << 1)) : 
    SET_PC(GET_PC() + (cur_instr - first_instr + 1) * 4); 
    CMD_incr(cur_instr - first_instr + 1);
}

void BLTExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    static_cast<int32_t>(RS1v) < static_cast<int32_t>(RS2v) ?
    SET_PC(GET_PC() + (cur_instr - first_instr) * 4 + (IMM << 1)) :
    SET_PC(GET_PC() + (cur_instr - first_instr + 1) * 4); 
    CMD_incr(cur_instr - first_instr + 1);
}

void BGEExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    static_cast<int32_t>(RS1v) >= static_cast<int32_t>(RS2v) ? 
    SET_PC(GET_PC() + (cur_instr - first_instr) * 4 + (static_cast<int32_t>(IMM) << 1)) :
    SET_PC(GET_PC() + (cur_instr - first_instr + 1) * 4); 
    CMD_incr(cur_instr - first_instr + 1);
}

void BLTUExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    RS1v < RS2v ? 
    SET_PC(GET_PC() + (cur_instr - first_instr) * 4 + (IMM << 1)) :
    SET_PC(GET_PC() + (cur_instr - first_instr + 1) * 4); 
    CMD_incr(cur_instr - first_instr + 1);
}

void BGEUExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    RS1v > RS2v ?
    SET_PC(GET_PC() + (cur_instr - first_instr) * 4 + (IMM << 1)) :
    SET_PC(GET_PC() + (cur_instr - first_instr + 1) * 4); 
    CMD_incr(cur_instr - first_instr + 1);
}

void JALExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, GET_PC() + 4 + (cur_instr - first_instr) * 4);
    SET_PC(GET_PC() + (cur_instr - first_instr) * 4 + (static_cast<int32_t>(IMM) << 1));
    CMD_incr(cur_instr - first_instr + 1);
}

void JALRExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, GET_PC() + (cur_instr - first_instr) * 4 + 4);
    SET_PC((RS1v + IMM) & 0xFFFFFFFE);  
    CMD_incr(cur_instr - first_instr + 1);
}

void SLLIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v << (IMM & 0b11111));
    NEXT_INSTR;
}

void SRLIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v >> (IMM & 0b11111));
    NEXT_INSTR;
}

void SRAIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    uint32_t sb_copy = static_cast<int32_t>(IMM) < 0 ? ~(~0u >> IMM) : 0;
    SET_R(RDn, (RS1v >> IMM) | sb_copy);
    NEXT_INSTR;
}

void ADDExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v + RS2v);
    NEXT_INSTR;
}

void SUBExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v - RS2v);
    NEXT_INSTR;
}

void SLLExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v << RS2v);
    NEXT_INSTR;
}

void SLTExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    static_cast<int32_t>(RS1v) < static_cast<int32_t>(RS2v) ? 
    SET_R(RDn, 1):
    SET_R(RDn, 0);
    NEXT_INSTR;
}

void SLTUExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    RS1v < RS2v ? 
    SET_R(RDn, 1):
    SET_R(RDn, 0);
    NEXT_INSTR;
}

void XORExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v ^ RS2v);
    NEXT_INSTR;
}

void SRLExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v >> (RS2v & 0b11111));
    NEXT_INSTR;
}

void SRAExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    uint8_t offs = RS2v & 0b11111;
    uint32_t sb_copy = static_cast<int8_t>(RS1v) < 0 ? ~(~0xFFFFFFFF >> offs) : 0; 
    SET_R(RDn, (RS1v >> offs) | sb_copy);
    NEXT_INSTR;
}

void ORExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v | RS2v);
    NEXT_INSTR;
}

void ANDExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v & RS2v);
    NEXT_INSTR;
}

void DUMMYExec  ([[maybe_unused]] const Instruction* first_instr, [[maybe_unused]] const Instruction* cur_instr, [[maybe_unused]] HartState* hart_state)
{
    throw DummyException("DUMMY instruction\n");
}

void ECALLExec  ([[maybe_unused]] const Instruction* first_instr,[[maybe_unused]] const Instruction* cur_instr,[[maybe_unused]] HartState* hart_state)
{
    CMD_incr(cur_instr - first_instr + 1);
    throw FinishException ("Finished execution!\n");
}

void MULExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v * RS2v);    
    NEXT_INSTR;
}

void MULHExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, ((static_cast<int64_t>(RS1v)*static_cast<int64_t>(RS2v))) >> 32);
    NEXT_INSTR;
}

void MULHSUExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, ((static_cast<int64_t>(RS1v)*static_cast<uint64_t>RS2v)) >> 32);
    NEXT_INSTR;
}

void MULHUExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, (static_cast<uint64_t>RS1v * static_cast<uint64_t>RS2v) >> 32);
    NEXT_INSTR;
}

void DIVExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    if (RS2v == 0)
        throw CalcException("Division by zero!\n");
    SET_R(RDn, static_cast<int32_t>(RS1v) / static_cast<int32_t>(RS2v));
    NEXT_INSTR;
}

void DIVUExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS2v ? RS1v / RS2v : UINT32_MAX);
    NEXT_INSTR;
}

void REMExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    if (RS2v == 0)
        SET_R(RDn, RS1v);
    SET_R(RDn, static_cast<int32_t>(RS1v) % static_cast<int32_t>(RS2v));
    NEXT_INSTR;
}

void REMUExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS2v? RS1v % RS2v : RS1v);
    NEXT_INSTR;
}

void BASICDUMMY (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_PC (GET_PC() + (cur_instr - first_instr) * 4);
    CMD_incr(cur_instr - first_instr);
}

void CSRRWExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    if (IMM != 0x180)
        throw RegException("Only SATP system register is supported!\n");
    SET_R(RDn, GET_SATP());
    SET_SATP(RS1v);
    NEXT_INSTR;
}

void CSRRSExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    if (IMM != 0x180)
        throw RegException("Only SATP system register is supported!\n");
    SET_R(RDn, GET_SATP());
    SET_SATP(GET_SATP() | RS1v);
    NEXT_INSTR;
}

void CSRRCExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    if (IMM != 0x180)
        throw RegException("Only SATP system register is supported!\n");
    SET_R(RDn, GET_SATP());
    SET_SATP(GET_SATP() | (!RS1v));
    NEXT_INSTR;
}

void CSRRWIExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    if (IMM != 0x180)
        throw RegException("Only SATP system register is supported!\n");
    SET_R(RDn, GET_SATP());
    SET_SATP(static_cast<uint32_t>(RS1n)); //the uimm is formally in rs1 field of I-TYPE instr
    NEXT_INSTR;
}

void CSRRSIExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    if (IMM != 0x180)
        throw RegException("Only SATP system register is supported!\n");
    SET_R(RDn, GET_SATP());
    SET_SATP(GET_SATP() | static_cast<uint32_t>(RS1n));
    NEXT_INSTR;
}

void CSRRCIExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    if (IMM != 0x180)
        throw RegException("Only SATP system register is supported!\n");
    SET_R(RDn, GET_SATP());
    SET_SATP(GET_SATP() | (!static_cast<uint32_t>(RS1n)));
    NEXT_INSTR;
}

/*
void LWADDIExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, static_cast<int32_t>(hart_state->ReadWord (IMM + RS1v)));
    SET_R(sRDn, nRS1v + static_cast<int32_t>(eIMM)); 
    NEXT_2_INSTR;
}

void SLLIADDExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v << (IMM & 0b11111));
    SET_R(sRDn, nRS1v + nRS2v);
    NEXT_2_INSTR;
}
*/

void SLLIADDLWExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v << (IMM & 0b11111));
    SET_R(sRDn, sRS1v + sRS2v);
    SET_R(tRDn, static_cast<int32_t>(hart_state->ReadWord (tIMM + tRS1v)));
    NEXT_3_INSTR;
}

void ADDISWLWExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state)
{
    SET_R(RDn, RS1v + static_cast<int32_t>(IMM)); 
    hart_state->WriteWord (sIMM + static_cast<int32_t>(sRS1v), sRS2v);
    SET_R(tRDn, static_cast<int32_t>(hart_state->ReadWord (tIMM + tRS1v)));
    NEXT_3_INSTR;
}

#endif
