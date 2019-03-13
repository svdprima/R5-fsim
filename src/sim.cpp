#include <chrono>
#include <stdexcept>
#include "sim.hpp"

void Sim::Execute ()
{
    std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
    Instruction dec_instr;
    try
    {
        uint32_t cur_instr_addr = 0;
        BasicBlock* BB;
        BasicBlock BB_new;
        while (true)
        {
            cur_instr_addr = hart_state.GetPc();
            BB = InstrCache.get(cur_instr_addr);
            if (BB == NULL)
            {
                BB_new = BasicBlock (hart_state, DCD);
                InstrCache.put (cur_instr_addr, BB_new);
                BB = &BB_new;
            }
            BB->ExecuteBlock (hart_state);
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
    std::chrono::high_resolution_clock::time_point t_finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> ex_time = std::chrono::duration_cast<std::chrono::duration<double>>(t_finish - t_start);
    printf ("%u instructions executed\n", hart_state.GetCmdCount());
    printf ("The execution time is %lf seconds\n", ex_time.count());
    printf ("Simulation speed is %.02lf MIPS\n", hart_state.GetCmdCount() / ex_time.count() / 1000000);
    printf ("Basic Block hit rate is %.06lf\n\t   miss rate is %.06lf\n", 
    (double)(InstrCache.GetHitCount())  / ((double)(InstrCache.GetHitCount() + InstrCache.GetMissCount())),
    (double)(InstrCache.GetMissCount()) / ((double)(InstrCache.GetHitCount() + InstrCache.GetMissCount())));
}

BasicBlock::BasicBlock (HartState &h_state, Decoder &DCD)
{
    uint32_t i = 0;
    uint32_t cur_instr = 0;
    do 
    {
        cur_instr = h_state.Fetch(h_state.GetPc() + 4 * i);
        instructions[i] = DCD.Decode(cur_instr);
        i++;
    }
    while ((i < block_size) && instructions[i - 1].GetBBEnd());
    instructions[i].SetCommand("BASIC", &BASICDUMMY);
}

inline void BasicBlock::ExecuteBlock (HartState& h_state)
{
    instructions.front().ExecCommand(&(instructions.front()), &h_state);     
}
