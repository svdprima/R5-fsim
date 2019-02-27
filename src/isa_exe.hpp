#ifndef ISA_EXE_HPP
#define ISA_EXE_HPP

#include <cstdlib>
#include "decoder.hpp"
#include "hart_state.h"

class Instruction;

void Execute (uint32_t &raw_instr, HartState* hart_state);

//RV32I Base Instruction Set

void LUIExec    (const Instruction* instr, HartState* hart_state);
void AUIPCExec  (const Instruction* instr, HartState* hart_state);
void JALExec    (const Instruction* instr, HartState* hart_state);
void JALRExec   (const Instruction* instr, HartState* hart_state);
void BEQExec    (const Instruction* instr, HartState* hart_state);
void BNEExec    (const Instruction* instr, HartState* hart_state);
void BLTExec    (const Instruction* instr, HartState* hart_state);
void BGEExec    (const Instruction* instr, HartState* hart_state);
void BLTUExec   (const Instruction* instr, HartState* hart_state);
void BGEUExec   (const Instruction* instr, HartState* hart_state);
void LBExec     (const Instruction* instr, HartState* hart_state);
void LHExec     (const Instruction* instr, HartState* hart_state);
void LWExec     (const Instruction* instr, HartState* hart_state);
void LBUExec    (const Instruction* instr, HartState* hart_state);
void LHUExec    (const Instruction* instr, HartState* hart_state);
void SBExec     (const Instruction* instr, HartState* hart_state);
void SHExec     (const Instruction* instr, HartState* hart_state);
void SWExec     (const Instruction* instr, HartState* hart_state);
void ADDIExec   (const Instruction* instr, HartState* hart_state);
void SLTIExec   (const Instruction* instr, HartState* hart_state);
void SLTIUExec  (const Instruction* instr, HartState* hart_state);
void XORIExec   (const Instruction* instr, HartState* hart_state);
void ORIExec    (const Instruction* instr, HartState* hart_state);
void ANDIExec   (const Instruction* instr, HartState* hart_state);
void SLLIExec   (const Instruction* instr, HartState* hart_state);
void SRLIExec   (const Instruction* instr, HartState* hart_state);
void SRAIExec   (const Instruction* instr, HartState* hart_state);
void ADDExec    (const Instruction* instr, HartState* hart_state);
void SUBExec    (const Instruction* instr, HartState* hart_state);
void SLLExec    (const Instruction* instr, HartState* hart_state);
void SLTExec    (const Instruction* instr, HartState* hart_state);
void SLTUExec   (const Instruction* instr, HartState* hart_state);
void XORExec    (const Instruction* instr, HartState* hart_state);
void SRLExec    (const Instruction* instr, HartState* hart_state);
void SRAExec    (const Instruction* instr, HartState* hart_state);
void ORExec     (const Instruction* instr, HartState* hart_state);
void ANDExec    (const Instruction* instr, HartState* hart_state);
//void FENCEExec  (const Instruction* instr, HartState* hart_state);
//void FENCEIExec (const Instruction* instr, HartState* hart_state);
void ECALLExec  (const Instruction* instr, HartState* hart_state);
//void EBREAKExec (const Instruction* instr, HartState* hart_state);
//void CSRRWExec  (const Instruction* instr, HartState* hart_state);
//void CSRRSExec  (const Instruction* instr, HartState* hart_state);
//void CSRRCExec  (const Instruction* instr, HartState* hart_state);
//void CSRRWIExec (const Instruction* instr, HartState* hart_state);
//void CSRRSIExec (const Instruction* instr, HartState* hart_state);
//void CSRRCIExec (const Instruction* instr, HartState* hart_state);
void DUMMYExec  (const Instruction* instr, HartState* hart_state);

//RV32M Standard Extension

void MULExec    (const Instruction* instr, HartState* hart_state);
void MULHExec   (const Instruction* instr, HartState* hart_state);
void MULHSUExec (const Instruction* instr, HartState* hart_state);
void MULHUExec  (const Instruction* instr, HartState* hart_state);
void DIVExec    (const Instruction* instr, HartState* hart_state);
void DIVUExec   (const Instruction* instr, HartState* hart_state);
void REMExec    (const Instruction* instr, HartState* hart_state);
void REMUExec   (const Instruction* instr, HartState* hart_state);
void DUMMYExec  (const Instruction* instr, HartState* hart_state);

#endif
