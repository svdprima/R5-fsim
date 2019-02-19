#ifndef ISA_EXE_HPP
#define ISA_EXE_HPP

#include <cstdlib>
#include "decoder.hpp"
#include "state.h"

class Instruction;

void Execute (uint32_t &raw_instr, State* state);

//RV32I Base Instruction Set

void LUIExec    (const Instruction* instr, State* state);
void AUIPCExec  (const Instruction* instr, State* state);
void JALExec    (const Instruction* instr, State* state);
void JALRExec   (const Instruction* instr, State* state);
void BEQExec    (const Instruction* instr, State* state);
void BNEExec    (const Instruction* instr, State* state);
void BLTExec    (const Instruction* instr, State* state);
void BGEExec    (const Instruction* instr, State* state);
void BLTUExec   (const Instruction* instr, State* state);
void BGEUExec   (const Instruction* instr, State* state);
void LBExec     (const Instruction* instr, State* state);
void LHExec     (const Instruction* instr, State* state);
void LWExec     (const Instruction* instr, State* state);
void LBUExec    (const Instruction* instr, State* state);
void LHUExec    (const Instruction* instr, State* state);
void SBExec     (const Instruction* instr, State* state);
void SHExec     (const Instruction* instr, State* state);
void SWExec     (const Instruction* instr, State* state);
void ADDIExec   (const Instruction* instr, State* state);
void SLTIExec   (const Instruction* instr, State* state);
void SLTIUExec  (const Instruction* instr, State* state);
void XORIExec   (const Instruction* instr, State* state);
void ORIExec    (const Instruction* instr, State* state);
void ANDIExec   (const Instruction* instr, State* state);
void SLLIExec   (const Instruction* instr, State* state);
void SRLIExec   (const Instruction* instr, State* state);
void SRAIExec   (const Instruction* instr, State* state);
void ADDExec    (const Instruction* instr, State* state);
void SUBExec    (const Instruction* instr, State* state);
void SLLExec    (const Instruction* instr, State* state);
void SLTExec    (const Instruction* instr, State* state);
void SLTUExec   (const Instruction* instr, State* state);
void XORExec    (const Instruction* instr, State* state);
void SRLExec    (const Instruction* instr, State* state);
void SRAExec    (const Instruction* instr, State* state);
void ORExec     (const Instruction* instr, State* state);
void ANDExec    (const Instruction* instr, State* state);
//void FENCEExec  (const Instruction* instr, State* state);
//void FENCEIExec (const Instruction* instr, State* state);
//void ECALLExec  (const Instruction* instr, State* state);
//void EBREAKExec (const Instruction* instr, State* state);
//void CSRRWExec  (const Instruction* instr, State* state);
//void CSRRSExec  (const Instruction* instr, State* state);
//void CSRRCExec  (const Instruction* instr, State* state);
//void CSRRWIExec (const Instruction* instr, State* state);
//void CSRRSIExec (const Instruction* instr, State* state);
//void CSRRCIExec (const Instruction* instr, State* state);
void DUMMYExec  (const Instruction* instr, State* state);
/*
enum class Cmds: uint8_t
{
    LUI,
    AUIPC,
    JAL,
    JALR,
    BEQ,
    BNE,
    BLT,
    BGE,
    BLTU,
    BGEU,
    LB,
    LH,
    LW,
    LBU,
    LHU,
    SB,
    SH,
    SW,
    ADDI,
    SLTI,
    SLTIU,
    XORI,
    ORI,
    ANDI,
    SLLI,
    SRLI,
    SRAI,
    ADD,
    SUB,
    SLL,
    SLT,
    SLTU,
    XOR,
    SRL,
    SRA,
    OR,
    AND,
    ECALL,
    EBREAK,
    URET,
    SRET,
    MRET,
    WFI,
    FENCE,
    CSRRW,
    CSRRS,
    CSRRC,
    CSRRWI,
    CSRRSI,
    CSRRCI,
    UNKNOWN
};
*/
#endif
