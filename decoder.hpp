#ifndef DECODER_HPP
#define DECODER_HPP

#include <vector>
#include <iostream>

enum InsrtType
{
    Undefined;
    RType;
    IType;
    SType;
    BType;  
    UType;
    JType;
};

class Instruction
{
private:
    char oppcode;
    char rd;
    char func3;
    char rs1;
    char rs2;
    char funct7;
    int imm;
    InstrType type;
public:
    Instruction ()
    {
        oppcode = 0;
        rd      = 0;
        func3   = 0;
        rs1     = 0;
        rs2     = 0;
        func7   = 0;
        imm     = 0;
        type = Undefined;
    }
    void Decode (int raw_instr);
    ~Instruction ();
};

#endif
