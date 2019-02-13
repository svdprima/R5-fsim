#ifndef DECODER_HPP
#define DECODER_HPP

#include <vector>
#include <iostream>

enum InstrType
{
    Undefined,
    RType,
    IType,
    SType,
    BType,  
    UType,
    JType
};

class Instruction
{
public:
    uint8_t oppcode;
    uint8_t rd;
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t funct7;
    uint32_t imm;
    InstrType type;
    Instruction ()
    {
        oppcode = 0;
        rd      = 0;
        funct3   = 0;
        rs1     = 0;
        rs2     = 0;
        funct7   = 0;
        imm     = 0;
        type = Undefined;
    }
    void Decode (uint32_t raw_instr);

    //~Instruction ();
};

#endif
