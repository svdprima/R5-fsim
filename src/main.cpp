#include "elf_reader.h"
#include "decoder.hpp"
#include "aux.hpp"
#include <stdio.h>

int main(int argc, char** argv)
{
    if(argc != 2)
        errx(EXIT_FAILURE, "usage : %s elf_file", argv[0]);

    Elf_reader ER;
    uint32_t PC = 0;
    std::vector<uint32_t> words;

    ER.Init(argv[1]);
    ER.Load(words);

    PC = ER.Entry();
    uint32_t n_pages = 20;
    Hart_state hart_state(PC, words, n_pages);
    
    Decoder DCD = Decoder ();
    Instruction decoded_instr = Instruction ();
    bool is_verbose = true;
    try
    {
        while (true)
        {
            decoded_instr = DCD.Decode (hart_state.Fetch(hart_state.GetPc()));
            decoded_instr.PrintInstr(is_verbose);
            decoded_instr.Exec_Command (&hart_state);
        }
    }
    catch (HartException &exc)
    {
        printf ("%s", exc.what());
    }
    hart_state.MemDump();
    return 0;
}
