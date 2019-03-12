#include <chrono>
#include <stdexcept>
#include "sim.hpp"

void Sim::Execute (bool is_verbose)
{
    std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
    Instruction dec_instr;
    try
    {
        uint32_t cur_instr_addr = 0;
        BasicBlock BB;
        while (true)
        {
            cur_instr_addr = hart_state.GetPc();
            if (InstrCache.is_in_cache(cur_instr_addr))
            {
                BB = InstrCache.get(cur_instr_addr);
                InstrCache.Hit();
            }
            else
            {
                BB = BasicBlock (hart_state, DCD);
                InstrCache.put (cur_instr_addr, BB);
                InstrCache.Miss();
            }
            BB.ExecuteBlock (hart_state);
            if (hart_state.GetCmdCount() >= MAX_INSTR)
            {
                printf ("Maximum number of instructions has been reached!\n");
                break;
            }
        }
    }
    catch (FinishException &exc)
    {
        printf ("%s", exc.what());
    }
    catch (DummyException &exc)
    {
        printf ("%s", exc.what());
    }
    catch (CalcException &exc)
    {
        printf ("%s", exc.what());
    }
    catch (RegException &exc)
    {
        printf ("%s", exc.what());
    }
    catch (OutOfMemException &exc)
    {
        printf ("%s", exc.what());
        printf ("Physical address : 0x%lx\n", exc.GetPa());
    }
    catch (UnalignException &exc)
    {
        printf ("%s", exc.what());
        printf ("Physical address : 0x%lx\n", exc.GetPa());
        hart_state.MemDump();
    }
    catch (PageFaultException &exc)
    {
        printf ("%s", exc.what());
        printf ("PTE : 0x%x\n", exc.GetPte());
        printf ("PTE address : 0x%lx\n", exc.GetPteAddr());
        hart_state.MemDump();
    }
    catch (std::range_error &err)
    {
        printf ("%s", err.what());
    }
    std::chrono::high_resolution_clock::time_point t_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> ex_time = std::chrono::duration_cast<std::chrono::duration<double>>(t_finish - t_start);
    printf ("%u instructions executed\n", hart_state.GetCmdCount());
    printf ("The execution time is %lf seconds\n", ex_time.count());
    printf ("Simulation speed is %.02lf MIPS\n", hart_state.GetCmdCount() / ex_time.count() / 1000000);
    printf ("Basic Block rate is %02lf, miss rate is %02lf\n", 
    (double)(InstrCache.GetHitCount())  / ((double)(InstrCache.GetHitCount() + InstrCache.GetMissCount())),
    (double)(InstrCache.GetMissCount()) / ((double)(InstrCache.GetHitCount() + InstrCache.GetMissCount())));
}

BasicBlock::BasicBlock (HartState &h_state, Decoder &DCD)
{
    uint32_t i = 0;
    uint32_t oppc = 0;
    uint32_t cur_instr = 0;
    do 
    {
        cur_instr = h_state.Fetch(h_state.GetPc() + 4 * i);
        instructions[i] = DCD.Decode(cur_instr);
        oppc = instructions[i].GetOppcode();
        i++;
    }
    while ((i < block_size) &&  oppc != 0b1101111
                                      &&  oppc != 0b1100111
                                      &&  oppc != 0b1100011
                                      && (oppc != 0b1110011
                    ||  instructions.at(i - 1).GetFunct3()));
    instructions[block_size].SetCommand("BASIC", &BASICDUMMY);
}

inline void BasicBlock::ExecuteBlock (HartState& h_state)
{
    instructions.front().ExecCommand(&(instructions.front()), &h_state);     
}
