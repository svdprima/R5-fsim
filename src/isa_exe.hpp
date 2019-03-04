#ifndef ISA_EXE_HPP
#define ISA_EXE_HPP

#include <cstdlib>
#include "decoder.hpp"
#include "hart_state.h"

class Instruction;

void Execute (uint32_t &raw_instr, HartState* hart_state);

//RV32I Base Instruction Set

void LUIExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void AUIPCExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void JALExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void JALRExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void BEQExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void BNEExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void BLTExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void BGEExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void BLTUExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void BGEUExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void LBExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void LHExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void LWExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void LBUExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void LHUExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SBExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SHExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SWExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void ADDIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SLTIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SLTIUExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void XORIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void ORIExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void ANDIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SLLIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SRLIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SRAIExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void ADDExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SUBExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SLLExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SLTExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SLTUExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void XORExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SRLExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void SRAExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void ORExec     (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void ANDExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
//void FENCEExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
//void FENCEIExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void ECALLExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
//void EBREAKExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void CSRRWExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void CSRRSExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void CSRRCExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void CSRRWIExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void CSRRSIExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void CSRRCIExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void BASICDUMMY (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void DUMMYExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);


//RV32M Standard Extension

void MULExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void MULHExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void MULHSUExec (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void MULHUExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void DIVExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void DIVUExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void REMExec    (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void REMUExec   (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);
void DUMMYExec  (const Instruction* first_instr, const Instruction* cur_instr, HartState* hart_state);

#endif
