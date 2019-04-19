#include "decoder.hpp"
#include "isa_exe.hpp"

Instruction Decoder::Decode (uint32_t raw_instr)
{
    Instruction dec_instr = Instruction ();
    int cur_oppc = 0b1111111 & raw_instr;
    int cur_funct3 = 0; 
    int cur_funct7 = 0; 
    //printf ("Raw instruction is: %08x\n", raw_instr);
   
    //RV32IM Instruction Set is currently supported
    if ((0b0010100 & cur_oppc) == 0b0010100)
    {
        dec_instr.type = InstrType::UType; 
        dec_instr.SetRd((0b111110000000 & raw_instr) >> 7);
        dec_instr.SetImm((0b11111111111111111111000000000000 & raw_instr) >> 12);
        if (dec_instr.GetImm() & 0b10000000000000000000)
            dec_instr.SetImm(dec_instr.GetImm() | 0b11111111111100000000000000000000);
    }
    else if (cur_oppc == 0b1101111)
    {
        dec_instr.type = InstrType::JType;
        dec_instr.SetRd((0b111110000000 & raw_instr) >> 7);
        dec_instr.SetImm((0b1111111111000000000000000000000 & raw_instr) >> 21);
        dec_instr.SetImm(dec_instr.GetImm() | (0b100000000000000000000 & raw_instr) >> 10);
        dec_instr.SetImm(dec_instr.GetImm() | (0b11111111000000000000 & raw_instr) >> 1);
        dec_instr.SetImm(dec_instr.GetImm() | (0b10000000000000000000000000000000 & raw_instr) >> 12);
        if (0b10000000000000000000000000000000 & raw_instr) //sign extension
            dec_instr.SetImm(dec_instr.GetImm() | 0b11111111111100000000000000000000); 
        dec_instr.SetBBEnd(false);
    }
    else if (cur_oppc == 0b0110011)
    {
        dec_instr.type  = InstrType::RType;
        dec_instr.SetRd((0b111110000000 & raw_instr) >> 7);
        cur_funct3 = (0b111000000000000 & raw_instr) >> 12;
        dec_instr.SetRs1((0b11111000000000000000 & raw_instr) >> 15);
        dec_instr.SetRs2((0b1111100000000000000000000 & raw_instr) >> 20);
        cur_funct7 = (0b11111110000000000000000000000000 & raw_instr) >> 25; 
    }

    else if (cur_oppc == 0b0000011 || cur_oppc == 0b0010011 || 
             cur_oppc == 0b1110011 || cur_oppc == 0b1100111)
    {
        dec_instr.type  = InstrType::IType;
        dec_instr.SetRd((0b111110000000 & raw_instr) >> 7);
        cur_funct3 = (0b111000000000000 & raw_instr) >> 12;
        dec_instr.SetRs1((0b11111000000000000000 & raw_instr) >> 15);
        dec_instr.SetImm((0b11111111111100000000000000000000 & raw_instr) >> 20);
        if (dec_instr.GetImm() & 0b100000000000)
            dec_instr.SetImm(dec_instr.GetImm() | 0b11111111111111111111000000000000);
        if (cur_oppc == 0b1100111 || (cur_oppc == 0b1110011 && !cur_funct3))
            dec_instr.SetBBEnd(false);
    }
    else if (cur_oppc == 0b0100011)
    {
        dec_instr.type = InstrType::SType;
        cur_funct3 = (0b111000000000000 & raw_instr) >> 12;
        dec_instr.SetRs1((0b11111000000000000000 & raw_instr) >> 15);
        dec_instr.SetRs2((0b1111100000000000000000000 & raw_instr) >> 20);
        dec_instr.SetImm((0b111110000000 & raw_instr) >> 7);
        dec_instr.SetImm(dec_instr.GetImm() | (0b11111110000000000000000000000000 & raw_instr) >> 20);
        if (dec_instr.GetImm() & 0b100000000000)
            dec_instr.SetImm (dec_instr.GetImm() | 0b11111111111111111111000000000000);
    }
    else if (cur_oppc == 0b1100011)
    {
        dec_instr.type = InstrType::BType;
        cur_funct3 = (0b111000000000000 & raw_instr) >> 12;
        dec_instr.SetRs1((0b11111000000000000000 & raw_instr) >> 15);
        dec_instr.SetRs2((0b1111100000000000000000000 & raw_instr) >> 20);
        dec_instr.SetImm((0b111100000000 & raw_instr) >> 8);
        dec_instr.SetImm(dec_instr.GetImm() | (0b1111110000000000000000000000000 & raw_instr) >> 21);
        dec_instr.SetImm(dec_instr.GetImm() | (0b10000000 & raw_instr) << 3);
        dec_instr.SetImm(dec_instr.GetImm() | (0b10000000000000000000000000000000 & raw_instr) >> 20);
        if (dec_instr.GetImm() & 0b100000000000)
            dec_instr.SetImm (dec_instr.GetImm() | 0b11111111111111111111000000000000);
        dec_instr.SetBBEnd(false);
    }
    uint8_t cmd_id = (cur_oppc >> 2) | (cur_funct3 << 5);
    if (!cur_funct7)
        dec_instr.SetCommand(SortedCommands.at(cmd_id)[0].c_name, SortedCommands.at(cmd_id)[0].exec_command);
    else
    {
        if (cur_funct7 == 0b1)
            dec_instr.SetCommand(SortedCommands.at(cmd_id).back().c_name, 
                                 SortedCommands.at(cmd_id).back().exec_command);
        else
            dec_instr.SetCommand(SortedCommands.at(cmd_id)[1].c_name,
                                 SortedCommands.at(cmd_id)[1].exec_command);
    }
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
            SortedCommands.at(cmd_id) =std::vector<CommandDescription> (1, CommandList[i]);
        else
            SortedCommands.at(cmd_id).push_back(CommandList[i]); //zero-funct7 command should go before non-zero funct7 one in CommandList   
    }
}

