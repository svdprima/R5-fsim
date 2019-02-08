#include "../decoder.hpp"

int main ()
{
    uint32_t LUI = 0b10101010101010101010111000010111;   
    Instruction lui = Instruction ();
    lui.Decode (LUI);
    if (lui.type != UType)
        printf ("UType parsed incorrectly!\n");
    if (lui.rd != 0b11100)
        printf ("rd parsed incorrectly!\n");
    if (lui.imm != 0b11111111111110101010101010101010)
        printf ("imm parsed incorrectly!\n");

    uint32_t JAL = 0b10000000000100000000111001101111;
    Instruction jal = Instruction ();
    jal.Decode (JAL);
    if (jal.type != JType)
        printf ("JType parsed incorrectly!\n");
    if (jal.rd != 0b11100)
        printf ("rd parsed incorrectly!\n");
    if (jal.imm != 0b11111111111110000000010000000000)
        printf ("imm parsed incorrectly!\n");
    
    uint32_t ADD = 0b00000001101100100101000100110011;
    Instruction add = Instruction ();
    add.Decode (ADD);
    if (add.type != RType)
        printf ("RType parsed incorrectly!\n");
    if (add.rd != 0b00010)
        printf ("rd parsed incorrectly!\n");
    if (add.funct3 != 0b101)
        printf ("funct3 parsed incorrectly!\n");
    if (add.rs1 != 0b00100)
        printf ("rs1 parsed incorrectly!\n");
    if (add.rs2 != 0b11011)
        printf ("rs2 parsed incorrectly!\n");
    if (add.funct7 != 0b0000000)
        printf ("funct7 parsed incorrectly!\n");

    uint32_t LB = 0b10000110001100011000111000000011;
    Instruction lb = Instruction ();
    lb.Decode (LB);
    if (lb.type != IType)
        printf ("IType parsed incorrectly!\n"); 
    if (lb.rd != 0b11100)
        printf ("rd parsed incorrectly!\n");
    if (lb.funct3 != 0b000)
        printf ("funct3 parsed incorrectly!\n");
    if (lb.rs1 != 0b00011)
        printf ("rs1 parsed incorrectly!\n");
    if (lb.imm != 0b11111111111111111111100001100011)
        printf ("imm parsed incorrectly!\n");

    uint32_t SB = 0b10101110001100001000001000100011;
    Instruction sb = Instruction ();
    sb.Decode (SB);
    if (sb.type != SType)
        printf ("Stype decoded incorrectly!\n");
    if (sb.funct3 != 0b000)
        printf ("funct3 decoded incorrectly!\n");
    if (sb.rs1 != 0b00001)
        printf ("rs1 decoded incorrectly!\n");
    if (sb.rs2 != 0b00011)
        printf ("rs2 decoded incorrectly!\n");
    if (sb.imm != 0b11111111111111111111101011100100)
        printf ("imm decoded incorrectly!\n");

    uint32_t BEQ = 0b11010100001100100000101001100011;
    Instruction beq = Instruction ();
    beq.Decode (BEQ);
    if (beq.type != BType)
        printf ("BType decoded incorrectly!\n");
    if (beq.funct3 != 0b000)
        printf ("funct3 decoded incorrectly!\n");
    if (beq.rs1 != 0b00100)
        printf ("rs1 decoded incorrectly!\n");
    if (beq.rs2 != 0b00011)
        printf ("rs2 decoded incorrectly!\n");
    if (beq.imm != 0b11111111111111111111101010101010)
        printf ("Bimm decoded incorrectly!\n");  
    return 0;
}
