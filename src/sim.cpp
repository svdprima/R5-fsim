#include "sim.hpp"
#include <chrono>

void Sim::Execute (bool is_verbose)
{
    std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
    Instruction dec_instr;
    try
    {
        while (true)
        {

            /*
            dec_instr = DCD.Decode(hart_state.Fetch(hart_state.GetPc()));
            //dec_instr.PrintInstr(verbose);
            dec_instr.ExecCommand (&hart_state);
            */
            BasicBlock BB = BasicBlock (hart_state, DCD);
            BB.ExecuteBlock (hart_state);
        }
    }
    catch (HartException &exc)
    {
        printf ("%s", exc.what());
    }
    std::chrono::high_resolution_clock::time_point t_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> ex_time = std::chrono::duration_cast<std::chrono::duration<double>>(t_finish - t_start);
    printf ("The execution time is %lf seconds\n", ex_time.count());
}

BasicBlock::BasicBlock (HartState &h_state, Decoder &DCD)
{
    uint32_t i = 0;
    do 
    {
        instructions[i] = DCD.Decode(h_state.Fetch(h_state.GetPc() + 4 * i)); 
        i++;
    }
    while ((i < block_size) && instructions.at(i - 1).GetOppcode() != 0b1101111
                            && instructions.at(i - 1).GetOppcode() != 0b1100111
                            && instructions.at(i - 1).GetOppcode() != 0b1100011
                            && instructions.at(i - 1).GetOppcode() != 0b1110011);
    instructions[block_size].SetCommand("BASIC", &BASICDUMMY);
}

inline void BasicBlock::ExecuteBlock (HartState& h_state)
{
    instructions.front().ExecCommand(&(instructions.front()), &h_state);     
}
