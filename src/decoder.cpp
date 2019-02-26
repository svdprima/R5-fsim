#include "decoder.hpp"

void Instruction::SetCommand (const char* c_name, void (*command) (const Instruction*, Hart_state*))
{
    command_name = c_name;
    cmd = command;
}

Instruction Decoder::Decode (uint32_t raw_instr)
{
    Instruction dec_instr = Instruction ();
    dec_instr.SetOppcode (0b1111111 & raw_instr);
   
    //RV32I Base Instruction Set is currently supported
    if ((0b0010100 & dec_instr.GetOppcode()) == 0b0010100)
    {
        dec_instr.type = InstrType::UType; 
        dec_instr.SetRd((0b111110000000 & raw_instr) >> 7);
        dec_instr.SetImm((0b11111111111111111111000000000000 & raw_instr) >> 12);
        if (dec_instr.GetImm() & 0b10000000000000000000)
            dec_instr.SetImm(dec_instr.GetImm() | 0b11111111111100000000000000000000);
    }
    else if (dec_instr.GetOppcode() == 0b1101111)
    {
        dec_instr.type = InstrType::JType;
        dec_instr.SetRd((0b111110000000 & raw_instr) >> 7);
        dec_instr.SetImm((0b1111111111000000000000000000000 & raw_instr) >> 21);
        dec_instr.SetImm(dec_instr.GetImm() | (0b100000000000000000000 & raw_instr) >> 10);
        dec_instr.SetImm(dec_instr.GetImm() | (0b11111111000000000000 & raw_instr));
        dec_instr.SetImm(dec_instr.GetImm() | (0b10000000000000000000000000000000 & raw_instr) >> 12);
        if (0b10000000000000000000000000000000 & raw_instr) //sign extension
            dec_instr.SetImm(dec_instr.GetImm() | 0b11111111111100000000000000000000); 
    }
    else if (dec_instr.GetOppcode() == 0b0110011)
    {
        dec_instr.type  = InstrType::RType;
        dec_instr.SetRd((0b111110000000 & raw_instr) >> 7);
        dec_instr.SetFunct3((0b111000000000000 & raw_instr) >> 12);
        dec_instr.SetRs1((0b11111000000000000000 & raw_instr) >> 15);
        dec_instr.SetRs2((0b1111100000000000000000000 & raw_instr) >> 20);
        dec_instr.SetFunct7((0b11111110000000000000000000000000 & raw_instr) >> 25); 
    }

    else if (dec_instr.GetOppcode() == 0b0000011 || dec_instr.GetOppcode() == 0b0010011 || 
             dec_instr.GetOppcode() == 0b1110011 || dec_instr.GetOppcode() == 0b1100111)
    {
        dec_instr.type  = InstrType::IType;
        dec_instr.SetRd((0b111110000000 & raw_instr) >> 7);
        dec_instr.SetFunct3((0b111000000000000 & raw_instr) >> 12);
        dec_instr.SetRs1((0b11111000000000000000 & raw_instr) >> 15);
        dec_instr.SetImm((0b11111111111100000000000000000000 & raw_instr) >> 20);
        if (dec_instr.GetImm() & 0b100000000000)
            dec_instr.SetImm(dec_instr.GetImm() | 0b11111111111111111111000000000000);
    }
    else if (dec_instr.GetOppcode() == 0b0100011)
    {
        dec_instr.type = InstrType::SType;
        dec_instr.SetFunct3((0b111000000000000 & raw_instr) >> 12);
        dec_instr.SetRs1((0b11111000000000000000 & raw_instr) >> 15);
        dec_instr.SetRs2((0b1111100000000000000000000 & raw_instr) >> 20);
        dec_instr.SetImm((0b111110000000 & raw_instr) >> 7);
        dec_instr.SetImm(dec_instr.GetImm() | (0b11111110000000000000000000000000 & raw_instr) >> 20);
        if (dec_instr.GetImm() & 0b100000000000)
            dec_instr.SetImm (dec_instr.GetImm() | 0b11111111111111111111000000000000);
    }
    else if (dec_instr.GetOppcode() == 0b1100011)
    {
        dec_instr.type = InstrType::BType;
        dec_instr.SetFunct3((0b111000000000000 & raw_instr) >> 12);
        dec_instr.SetRs1((0b11111000000000000000 & raw_instr) >> 15);
        dec_instr.SetRs2((0b1111100000000000000000000 & raw_instr) >> 20);
        dec_instr.SetImm((0b111100000000 & raw_instr) >> 8);
        dec_instr.SetImm(dec_instr.GetImm() | (0b1111110000000000000000000000000 & raw_instr) >> 21);
        dec_instr.SetImm(dec_instr.GetImm() | (0b10000000 & raw_instr) << 3);
        dec_instr.SetImm(dec_instr.GetImm() | (0b10000000000000000000000000000000 & raw_instr) >> 20);
        if (dec_instr.GetImm() & 0b100000000000)
            dec_instr.SetImm (dec_instr.GetImm() | 0b11111111111111111111000000000000);
    }
    uint8_t cmd_id = (dec_instr.GetOppcode() >> 2) | (dec_instr.GetFunct3() << 5);
    if (!dec_instr.GetFunct7())
        dec_instr.SetCommand(SortedCommands.at(cmd_id)[0].c_name, SortedCommands.at(cmd_id)[0].exec_command);
    else
        dec_instr.SetCommand(SortedCommands.at(cmd_id)[0].c_name, SortedCommands.at(cmd_id)[1].exec_command);
    return dec_instr;
}

Decoder::Decoder ()
{
    uint8_t cmd_id = 0;
    std::vector <CommandDescription> dummy_vec (1, CommandList[Decoder::GetCommandNu()]);
    SortedCommands.fill(dummy_vec);
    for (unsigned int i = 0; i < Decoder::GetCommandNu(); i++)
    {
        if (!(static_cast<uint8_t>(CommandList[i].oppcode) & 0b11))
        {
            printf ("Warning: the command's oppcode is out of RV32 Base ISA's scope\n");
        }
        cmd_id = (static_cast<uint8_t>(CommandList[i].oppcode) >> 2) | (CommandList[i].funct3 << 5);
        if (!CommandList[i].funct7)
        {
            SortedCommands.at(cmd_id) =std::vector<CommandDescription> (1, CommandList[i]);
        }
        else
        {
            SortedCommands.at(cmd_id).insert(SortedCommands.at(cmd_id).end(), CommandList[i]); //zero-funct7 command should go before non-zero funct7 one in CommandList   
        }
    }
}

uint8_t Instruction::GetOppcode () const
{
    return oppcode;
}

uint8_t Instruction::GetRd () const
{
    return rd;
}

uint8_t Instruction::GetFunct3 () const
{
    return funct3;
}

uint8_t Instruction::GetRs1 () const

{
    return rs1;
}

uint8_t Instruction::GetRs2 () const
{
    return rs2;
}

uint8_t Instruction::GetFunct7 () const
{
    return funct7;
}

uint32_t Instruction::GetImm () const
{
    return imm;
}

void Instruction::SetOppcode (uint8_t oppc)
{
    oppcode = oppc;
}

void Instruction::SetRd (uint8_t RD)
{
    rd = RD;
}

void Instruction::SetFunct3 (uint8_t f3)
{
    funct3 = f3;
}

void Instruction::SetRs1 (uint8_t RS1)
{
    rs1 = RS1;
}

void Instruction::SetRs2 (uint8_t RS2)
{
    rs2 = RS2;
}
void Instruction::SetFunct7 (uint8_t f7)
{
    funct7 = f7;
}

void Instruction::SetImm (uint32_t IMM)
{
    imm = IMM;
}

void Instruction::Exec_Command (Hart_state* hart_state)
{
    cmd (this, hart_state);
}

void Instruction::PrintInstr (const bool is_verbose)
{
    printf ("%s\n", command_name);
    if (is_verbose)
    {
        switch (type)
        {
            case InstrType::RType:
                printf ("RType\n");
                printf ("oppcode: %u\n", oppcode);
                printf ("rd     : %u\n", rd);
                printf ("funct3 : %u\n", funct3);
                printf ("rs1    : %u\n", rs1);
                printf ("rs2    : %u\n", rs2);
                printf ("funct7 : %u\n", funct7);
                break;
            case InstrType::IType:
                printf ("IType\n");
                printf ("oppcode: %u\n", oppcode);
                printf ("rd     : %u\n", rd);
                printf ("funct3 : %u\n", funct3);
                printf ("rs1    : %u\n", rs1);
                printf ("imm    : %u\n", imm);
                break;
            case InstrType::SType:
                printf ("SType\n");
                printf ("oppcode: %u\n", oppcode);
                printf ("funct3 : %u\n", funct3);
                printf ("rs1    : %u\n", rs1);
                printf ("rs2    : %u\n", rs2);
                printf ("imm    : %u\n", imm);
                break;
            case InstrType::BType:
                printf ("BType\n");
                printf ("oppcode: %u\n", oppcode);
                printf ("funct3 : %u\n", funct3);
                printf ("rs1    : %u\n", rs1);
                printf ("rs2    : %u\n", rs2);
                printf ("imm    : %u\n", imm);
                break;
            case InstrType::UType:
                printf ("UType\n");
                printf ("rd     : %u\n", rd);
                printf ("imm    : %u\n", imm);
                break;
            case InstrType::JType:
                printf ("JType\n");
                printf ("rd     : %u\n", rd);
                printf ("imm    : %u\n", imm);
                break;
            default:
                printf ("Type is undefined\n");
        }
        printf ("\n");
    }
}    
