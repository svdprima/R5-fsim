#include "decoder.hpp"

void Instruction::Decode (uint32_t raw_instr)
{
    oppcode = 0b1111111 & raw_instr;
   
    //RV32I Base Instruction Set is currently supported
    if ((0b0010100 & oppcode) == 0b0010100)
    {
        type = UType; 
        rd = (0b111110000000 & raw_instr) >> 7;
        imm = (0b11111111111111111111000000000000 & raw_instr) >> 12;
        if (imm & 0b10000000000000000000)
            imm |= 0b11111111111100000000000000000000;
    }
    else if (oppcode == 0b1101111)
    {
        type = JType;
        rd = (0b111110000000 & raw_instr) >> 7;
        imm  = (0b1111111111000000000000000000000 & raw_instr) >> 21;
        imm |= (0b100000000000000000000 & raw_instr) >> 10;
        imm |= (0b11111111000000000000 & raw_instr);
        imm |= (0b10000000000000000000000000000000 & raw_instr) >> 12;
        if (0b10000000000000000000000000000000 & raw_instr) //sign extension
            imm |= 0b11111111111100000000000000000000; 
    }
    else if (oppcode == 0b0110011)
    {
        type  = RType;
        rd    = (0b111110000000 & raw_instr) >> 7;
        funct3 = (0b111000000000000 & raw_instr) >> 12;
        rs1   = (0b11111000000000000000 & raw_instr) >> 15;
        rs2   = (0b1111100000000000000000000 & raw_instr) >> 20;
        funct7 = (0b11111110000000000000000000000000 & raw_instr) >> 25; 
    }

    else if (oppcode == 0b0000011 || oppcode == 0b0010011)
    {
        type  = IType;
        rd    = (0b111110000000 & raw_instr) >> 7;
        funct3 = (0b111000000000000 & raw_instr) >> 12;
        rs1   = (0b11111000000000000000 & raw_instr) >> 15;
        imm   = (0b11111111111100000000000000000000 & raw_instr) >> 20;
        if (imm & 0b100000000000)
            imm|= 0b11111111111111111111000000000000;
    }
    else if (oppcode == 0b0100011)
    {
        type = SType;
        funct3 = (0b111000000000000 & raw_instr) >> 12;
        rs1   = (0b11111000000000000000 & raw_instr) >> 15;
        rs2   = (0b1111100000000000000000000 & raw_instr) >> 20;
        imm   = (0b111110000000 & raw_instr) >> 7;
        imm  |= (0b11111110000000000000000000000000 & raw_instr) >> 20;
        if (imm & 0b100000000000)
            imm|= 0b11111111111111111111000000000000;
    }
    else if (oppcode == 0b1100011)
    {
        type = BType;
        funct3 = (0b111000000000000 & raw_instr) >> 12;
        rs1   = (0b11111000000000000000 & raw_instr) >> 15;
        rs2   = (0b1111100000000000000000000 & raw_instr) >> 20;
        imm   = (0b111100000000 & raw_instr) >> 8;
        imm  |= (0b1111110000000000000000000000000 & raw_instr) >> 21;
        imm  |= (0b10000000 & raw_instr) << 4;
        imm  |= (0b10000000000000000000000000000000 & raw_instr) >> 20;
        if (imm & 0b100000000000)
            imm |= 0b11111111111111111111000000000000;
    }
}
