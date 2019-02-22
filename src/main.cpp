#include "elf_reader.h"
#include "decoder.hpp"
#include "aux.hpp"
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
    bool is_verbose = true;
    try
    {
        while (true)
        {
            decoded_instr = DCD.Decode (state.ReadWord(state.GetPc()));
            decoded_instr.PrintInstr(is_verbose);
            decoded_instr.Exec_Command (&state);
        }
    }
    catch (HartException &exc)
    {
        printf ("%s", exc.what());
    }
    state.MemDump();
    return 0;
}
