#include "decoder.hpp"

void Instruction::Decode (int raw_instr)
{
    oppcode = 0b1111111 & raw_instr;
    //RV32I Base Instruction Set is currently supported
    if (!(0b01000 & oppcode))
    {
        type = UType; 
        rd = 0b111110000000 & raw_instr;
        imm = 0b11111111111111111111000000000000 & raw_instr;
    }
    else if (!(0b0010000 & oppcode))
    {
        type = JType;
        rd = 0b111110000000 & raw_instr;
        imm  = (0b1111111111000000000) & (raw_insrt) >> 9;
        imm |= 0b100000000 & raw_insrt;
        imm |= (0b11111111 & raw_insrt << 10);
        imm |= 0b10000000000000000000 & raw_insrt;
        if (0b10000000000000000000 & raw_insrt) //sign extension
            imm |= 0b1111111111100000000000000000000; 
    }
    else if (!(0b1001100 & oppcode))
    {
        type  = RType;
        rd    = (0b111110000000 & raw_insrt) >> 7;
        func3 = (0b111000000000000 & raw_insrt) >> 12;
        rs1   = (0b11111000000000000000 & raw_insrt) >> 15;
        rs2   = (0b1111100000000000000000000 & raw_instr) >> 20;
        func7 = (0b11111110000000000000000000000000 & raw_instr) >> 25; 
    }

    else if (!(0b1101100 & oppcode || 0b1111100 & raw_instr))
    {
        type  = IType;
        rd    = 0b111110000000 & raw_instr;
        func3 = (0b111000000000000 & raw_insrt) >> 12;
        rs1   = (0b11111000000000000000 & raw_insrt) >> 15;
        imm   = (0b11111111111100000000000000000000 & raw_insrt) >> 20;
        if (imm & 0b1000000000000)
            imm|= 0b111111111111111111110000000000000 & raw_instr;
    }
    else if (!(0b1011100 & oppcode))
    {
        type = SType;
        func3 = (0b111000000000000 & raw_insrt) >> 12;
        rs1   = (0b11111000000000000000 & raw_insrt) >> 15;
        rs2   = (0b1111100000000000000000000 & raw_instr) >> 20;
        imm   = (0b111110000000 & raw_insrt) >> 7;
        imm  |= (0b11111110000000000000000000000000 & raw_instr) >> 20;
        if (imm & 0b1000000000000)
            imm|= 0b111111111111111111110000000000000 & raw_instr;
    }
    else if (!(0b0011100 & oppcode))
    {
        type = BType;
        func3 = (0b111000000000000 & raw_insrt) >> 12;
        rs1   = (0b11111000000000000000 & raw_insrt) >> 15;
        rs2   = (0b1111100000000000000000000 & raw_instr) >> 20;
        imm   = (0b111100000000 & raw_instr) >> 8;
        imm  |= (0b1111110000000000000000000000000 & raw_instr) >> 25;
        imm  |= (0b10000000 & raw_instr) << 3;
        imm  |= (0b10000000000000000000000000000000 & raw_insrt) >> 20;
        if (0b10000000000000000000000000000000 & raw_insrt)
            imm |= 0b11111111111111111111000000000000;
    }
}
