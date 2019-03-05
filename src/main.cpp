#include "elf_reader.h"
#include "decoder.hpp"
#include "sim.hpp"
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
    uint32_t n_pages = 200;
    HartState hart_state(PC, words, n_pages);
    
    Sim sim = Sim (hart_state);
    bool is_verbose = true;
    sim.Execute (is_verbose);
    return 0;
}
