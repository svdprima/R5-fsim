#include "elf_reader.h"
#include "decoder.hpp"
#include <stdio.h>

int main(int argc, char** argv)
{
    Elf_reader ER;
    uint32_t PC = 0;
    std::vector<uint32_t> instr;

    ER.Init(argv[1]);
    ER.Load(instr);

    PC = ER.Entry();
    State state(PC, instr);
    
    Decoder DCD = Decoder ();
    Instruction decoded_instr = Instruction ();
    uint32_t cur_instr = 0;
    //while (cur_instr != 0x00008067)
    for (int i = 0; i < 1000 && cur_instr != 0x00008067; i++)
    {
        cur_instr = instr[state.GetPc()/4];
        decoded_instr = DCD.Decode (cur_instr);
        decoded_instr.PrintInstr();
        decoded_instr.Exec_Command (&state);
    }
    return 0;
}
