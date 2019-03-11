#ifndef DECODER_HPP
#define DECODER_HPP

#include <vector>
#include <iostream>
#include <array>
#include "hart_state.h"
#include "lru_cache.h"
#include "ir.hpp"

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

struct CommandDescription
{
    const char* c_name;
    void (*exec_command) (const Instruction*, const Instruction*, HartState*);
    Oppcodes oppcode;
    uint8_t funct3 = 0;
    uint8_t funct7 = 0;
};
const CommandDescription CommandList [] = 
{
    {"LUI",   &LUIExec,   Oppcodes::LUI},
    {"AUIPC", &AUIPCExec, Oppcodes::AUIPC},
    {"JAL",   &JALExec,   Oppcodes::JAL},
    {"JALR",  &JALRExec,  Oppcodes::JALR},
    {"BEQ",   &BEQExec,   Oppcodes::BRANCH},
    {"BNE",   &BNEExec,   Oppcodes::BRANCH,  0b001},
    {"BLT",   &BLTExec,   Oppcodes::BRANCH,  0b100},
    {"BGE",   &BGEExec,   Oppcodes::BRANCH,  0b101},
    {"BLTU",  &BLTUExec,  Oppcodes::BRANCH,  0b110},
    {"BGEU",  &BGEUExec,  Oppcodes::BRANCH,  0b111},
    {"LB",    &LBExec,    Oppcodes::LOAD },
    {"LH",    &LHExec,    Oppcodes::LOAD,    0b001},
    {"LW",    &LWExec,    Oppcodes::LOAD,    0b010},
    {"LBU",   &LBUExec,   Oppcodes::LOAD,    0b100},
    {"LHU",   &LHUExec,   Oppcodes::LOAD,    0b101},
    {"SB",    &SBExec,    Oppcodes::STORE},
    {"SH",    &SHExec,    Oppcodes::STORE,   0b001},
    {"SW",    &SWExec,    Oppcodes::STORE,   0b010},
    {"ADDI",  &ADDIExec,  Oppcodes::OPP_IMM},
    {"SLTI",  &SLTIExec,  Oppcodes::OPP_IMM, 0b010},
    {"SLTIU", &SLTIUExec, Oppcodes::OPP_IMM, 0b011},
    {"XORI",  &XORIExec,  Oppcodes::OPP_IMM, 0b100},
    {"ORI",   &ORIExec,   Oppcodes::OPP_IMM, 0b110},
    {"ANDI",  &ANDIExec,  Oppcodes::OPP_IMM, 0b111},
    {"SLLI",  &SLLIExec,  Oppcodes::OPP_IMM, 0b001},
    {"SRLI",  &SRLIExec,  Oppcodes::OPP_IMM, 0b101},
    {"SRAI",  &SRAIExec,  Oppcodes::OPP_IMM, 0b101, 0x20}, //that is not actual funct7, but a piece of imm
    {"ADD",   &ADDExec,   Oppcodes::OP},
    {"SUB",   &SUBExec,   Oppcodes::OP,      0b000, 0x20},
    {"SLL",   &SLLExec,   Oppcodes::OP,      0b001},
    {"SLT",   &SLTExec,   Oppcodes::OP,      0b010},
    {"SLTU",  &SLTUExec,  Oppcodes::OP,      0b011},
    {"XOR",   &XORExec,   Oppcodes::OP,      0b100},
    {"SRL",   &SRLExec,   Oppcodes::OP,      0b101},
    {"SRA",   &SRAExec,   Oppcodes::OP,      0b101, 0x20},
    {"OR",    &ORExec,    Oppcodes::OP,      0b110},
    {"AND",   &ANDExec,   Oppcodes::OP,      0b111},
    //{"FENCE", &FENCEExec, Oppcodes::MISC-MEM},
    //{"FENCEI",&FENCEIExec,Oppcodes::MISC-MEM,0b001},
    {"ECALL", &ECALLExec, Oppcodes::SYSTEM},
    //{"EBREAK",&EBREAKExec,Oppcodes::SYSTEM,  0b000, 0b1}, //not a funct7, but the entire imm
    {"CSRRW", &CSRRWExec, Oppcodes::SYSTEM,  0b001},
    {"CSRRS", &CSRRSExec, Oppcodes::SYSTEM,  0b010},
    {"CSRRC", &CSRRCExec, Oppcodes::SYSTEM,  0b011},
    {"CSRRWI",&CSRRWIExec,Oppcodes::SYSTEM,  0b101},
    {"CSRRSI",&CSRRSIExec,Oppcodes::SYSTEM,  0b110},
    {"CSRRCI",&CSRRCIExec,Oppcodes::SYSTEM,  0b111}, 

    {"DUMMY", &DUMMYExec, Oppcodes::UNINIT},
    {"MUL",   &MULExec,   Oppcodes::OP,      0b000, 0x1},
    {"MULH",  &MULHExec,  Oppcodes::OP,      0b001, 0x1},
    {"MULHSU",&MULHSUExec,Oppcodes::OP,      0b010, 0x1},
    {"MULHU", &MULHUExec, Oppcodes::OP,      0b011, 0x1},
    {"DIV",   &DIVExec,   Oppcodes::OP,      0b100, 0x1},
    {"DIVU",  &DIVUExec,  Oppcodes::OP,      0b101, 0x1},
    {"REM",   &REMExec,   Oppcodes::OP,      0b110, 0x1},
    {"REMU",  &REMUExec,  Oppcodes::OP,      0b111, 0x1},
    {"BASIC", &BASICDUMMY,Oppcodes::UNINIT}
};

class Decoder
{
private:
    std::array <std::vector<CommandDescription>, 256> SortedCommands;
    static constexpr uint8_t oppcode_nu = sizeof(OppcodeType) / sizeof(OppcodeType[0]);
    static constexpr uint8_t cmd_nu     = sizeof(CommandList) / sizeof(CommandList[0]);
public:
    Decoder ();
    uint8_t GetOppcodeNu ()
    {
        return oppcode_nu;
    };
    uint8_t GetCommandNu ()
    {
        return cmd_nu - 1;
    };
    Instruction Decode (uint32_t raw_instr);
};

#endif
