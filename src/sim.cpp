#include "sim.hpp"
#include <chrono>
#include <stdexcept>

void Sim::Execute (bool is_verbose)
{
    std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
    Instruction dec_instr;
    try
    {
        while (true)
        {

            BasicBlock BB = BasicBlock (hart_state, DCD);
            BB.ExecuteBlock (hart_state);
            if (hart_state.GetCmdCount() >= MAX_INSTR)
                break;
        }
    }
    catch (HartException &exc)
    {
        printf ("%s", exc.what());
        printf ("%u instructions executed\n", hart_state.GetCmdCount());
        hart_state.MemDump();
    }
    catch (std::range_error &err)
    {
        printf ("%s", err.what());
    }
    std::chrono::high_resolution_clock::time_point t_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> ex_time = std::chrono::duration_cast<std::chrono::duration<double>>(t_finish - t_start);
    printf ("The execution time is %lf seconds\n", ex_time.count());
    printf ("Simulation speed is %.02lf MIPS\n", hart_state.GetCmdCount() / ex_time.count() / 1000000);
    printf ("Hit rate is %02lf, miss rate is %02lf\n", (double)((double)(DCD.hit) / hart_state.GetCmdCount()), 
                                                       (double)((double)(DCD.miss) / hart_state.GetCmdCount()));
}

BasicBlock::BasicBlock (HartState &h_state, Decoder &DCD)
{
    uint32_t i = 0;
    do 
    {
        instructions[i] = DCD.Decode(h_state.Fetch(h_state.GetPc() + 4 * i)); 
        i++;
    }
    while ((i < block_size) &&  instructions.at(i - 1).GetOppcode() != 0b1101111
                            &&  instructions.at(i - 1).GetOppcode() != 0b1100111
                            &&  instructions.at(i - 1).GetOppcode() != 0b1100011
                            && (instructions.at(i - 1).GetOppcode() != 0b1110011
                            ||  instructions.at(i - 1).GetFunct3()));
    instructions[block_size].SetCommand("BASIC", &BASICDUMMY);
}

inline void BasicBlock::ExecuteBlock (HartState& h_state)
{
    instructions.front().ExecCommand(&(instructions.front()), &h_state);     
}
