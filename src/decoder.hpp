#ifndef DECODER_HPP
#define DECODER_HPP

#include <vector>
#include <iostream>
#include <array>
#include "isa_exe.hpp"
#include "state.h"

enum class InstrType: uint8_t
{
    Undefined,
    RType,
    IType,
    SType,
    BType,  
    UType,
    JType
};

enum class Oppcodes: uint8_t
{
    LUI      = 0b0110111,
    AUIPC    = 0b0010111,
    JAL      = 0b1101111,
    JALR     = 0b1100111,
    BRANCH   = 0b1100011,
    LOAD     = 0b0000011,
    STORE    = 0b0100011,
    OPP_IMM  = 0b0010011,
    OP       = 0b0110011,
    MISC_MEM = 0b0001111,
    SYSTEM   = 0b1110011,
    UNINIT   = 0b11  
};

struct OppcodeDescr
{
    Oppcodes oppcode;
    InstrType type;
};

const OppcodeDescr OppcodeType[] = 
{
    {Oppcodes::LUI,     InstrType::UType},
    {Oppcodes::AUIPC,   InstrType::UType},
    {Oppcodes::JAL,     InstrType::JType},
    {Oppcodes::JALR,    InstrType::IType},
    {Oppcodes::BRANCH,  InstrType::BType},
    {Oppcodes::LOAD,    InstrType::IType},
    {Oppcodes::STORE,   InstrType::SType},
    {Oppcodes::OPP_IMM, InstrType::IType},
    {Oppcodes::OP,      InstrType::RType},
    {Oppcodes::MISC_MEM,InstrType::IType},
    {Oppcodes::SYSTEM,  InstrType::IType}
};

class Instruction
{
private:
    uint8_t oppcode;
    uint8_t rd;
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t funct7;
    uint32_t imm;
    void (*cmd) (const Instruction*, State*);
    const char* command_name;
public:
    InstrType type;
    Instruction ()
    {
        oppcode = 0;
        rd      = 0;
        funct3  = 0;
        rs1     = 0;
        rs2     = 0;
        funct7  = 0;
        imm     = 0;
        type = InstrType::Undefined;
    }
    uint8_t GetOppcode () const;
    uint8_t GetRd () const;
    uint8_t GetFunct3 () const;
    uint8_t GetRs1 () const;
    uint8_t GetRs2 () const;
    uint8_t GetFunct7 () const;
    uint32_t GetImm () const;
    void Exec_Command (State* state);
    void SetOppcode (uint8_t oppc);
    void SetRd (uint8_t RD);
    void SetFunct3 (uint8_t f3);
    void SetRs1 (uint8_t RS1);
    void SetRs2 (uint8_t RS2);
    void SetFunct7 (uint8_t f7);
    void SetImm (uint32_t IMM);
    void SetCommand (const char* c_name, void (*command) (const Instruction*, State*));
    void PrintInstr (const bool is_verbose);
};

struct CommandDescription
{
    const char* c_name;
    void (*exec_command) (const Instruction*, State*);
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
    //{"CSRRW", &CSRRWExec, Oppcodes::SYSTEM,  0b001},
    //{"CSRRS", &CSRRSExec, Oppcodes::SYSTEM,  0b010},
    //{"CSRRC", &CSRRCExec, Oppcodes::SYSTEM,  0b011},
    //{"CSRRWI",&CSRRWIExec,Oppcodes::SYSTEM,  0b101},
    //{"CSRRSI",&CSRRSIExec,Oppcodes::SYSTEM,  0b110},
    //{"CSRRCI",&CSRRCIExec,Oppcodes::SYSTEM,  0b111}    
    {"DUMMY", &DUMMYExec, Oppcodes::UNINIT}
};

class Decoder
{
private:
    std::array <std::vector<CommandDescription>, 256> SortedCommands;
    const uint8_t oppcode_nu = sizeof(OppcodeType) / sizeof(OppcodeType[0]);
    const uint8_t cmd_nu     = sizeof(CommandList) / sizeof(CommandList[0]);
public:
    Decoder ();
    uint8_t GetOppcodeNu ()
    {
        return oppcode_nu;
    };
    uint8_t GetCommandNu ()
    {
        return cmd_nu - 1;
    }
    Instruction Decode (uint32_t raw_instr);
};
#endif
