#include <chrono>
#include <stdexcept>
#include "sim.hpp"

#include <map>
#include <vector>
#include <algorithm>
bool bb_pred(const std::pair< uint32_t, uint32_t > &a, const std::pair< uint32_t, uint32_t > &b)
{
    return a.second < b.second;
}
bool instr_pred(const std::pair< std::pair<uint8_t, uint8_t>, uint32_t > &a, 
                const std::pair< std::pair<uint8_t, uint8_t>, uint32_t > &b)
{
    return a.second < b.second;
}
const char* AddrToString(uint64_t address)
{
    if (address == (uint64_t)&LUIExec)
        return "LUIExec    ";
    if (address == (uint64_t)&AUIPCExec)
        return "AUIPCExec  ";
    if (address == (uint64_t)&JALExec)
        return "JALExec    ";
    if (address == (uint64_t)&JALRExec)
        return "JALRExec   ";
    if (address == (uint64_t)&BEQExec)
        return "BEQExec    ";
    if (address == (uint64_t)&BNEExec)
        return "BNEExec    ";
    if (address == (uint64_t)&BLTExec)
        return "BLTExec    ";
    if (address == (uint64_t)&BGEExec)
        return "BGEExec    ";
    if (address == (uint64_t)&BLTUExec)
        return "BLTUExec   ";
    if (address == (uint64_t)&BGEUExec)
        return "BGEUExec   ";
    if (address == (uint64_t)&LBExec)
        return "LBExec     ";
    if (address == (uint64_t)&LHExec)
        return "LHExec     ";
    if (address == (uint64_t)&LWExec)
        return "LWExec     ";
    if (address == (uint64_t)&LBUExec)
        return "LBUExec    ";
    if (address == (uint64_t)&LHUExec)
        return "LHUExec    ";
    if (address == (uint64_t)&SBExec)
        return "SBExec     ";
    if (address == (uint64_t)&SHExec)
        return "SHExec     ";
    if (address == (uint64_t)&SWExec)
        return "SWExec     ";
    if (address == (uint64_t)&ADDIExec)
        return "ADDIExec   ";
    if (address == (uint64_t)&SLTIExec)
        return "SLTIExec   ";
    if (address == (uint64_t)&SLTIUExec)
        return "SLTIUExec  ";
    if (address == (uint64_t)&XORIExec)
        return "XORIExec   ";
    if (address == (uint64_t)&ORIExec)
        return "ORIExec    ";
    if (address == (uint64_t)&ANDIExec)
        return "ANDIExec   ";
    if (address == (uint64_t)&SLLIExec)
        return "SLLIExec   ";
    if (address == (uint64_t)&SRLIExec)
        return "SRLIExec   ";
    if (address == (uint64_t)&SRAIExec)
        return "SRAIExec   ";
    if (address == (uint64_t)&ADDExec)
        return "ADDExec    ";
    if (address == (uint64_t)&SUBExec)
        return "SUBExec    ";
    if (address == (uint64_t)&SLLExec)
        return "SLLExec    ";
    if (address == (uint64_t)&SLTExec)
        return "SLTExec    ";
    if (address == (uint64_t)&SLTUExec)
        return "SLTUExec   ";
    if (address == (uint64_t)&XORExec)
        return "XORExec   ";
    if (address == (uint64_t)&SRLExec)
        return "SRLExec   ";
    if (address == (uint64_t)&SRAExec)
        return "SRAExec   ";
    if (address == (uint64_t)&ORExec)
        return "ORExec    ";
    if (address == (uint64_t)&ANDExec)
        return "ANDExec   ";
    if (address == (uint64_t)&ECALLExec)
        return "ECALLExec ";
    if (address == (uint64_t)&CSRRWExec)
        return "CSRRWExec ";
    if (address == (uint64_t)&CSRRSExec)
        return "CSRRSExec ";
    if (address == (uint64_t)&CSRRCExec)
        return "CSRRCExec ";
    if (address == (uint64_t)&CSRRWIExec)
        return "CSRRWIExec";
    if (address == (uint64_t)&CSRRSIExec)
        return "CSRRSIExec";
    if (address == (uint64_t)&CSRRCIExec)
        return "CSRRCIExec";
    if (address == (uint64_t)&BASICDUMMY)
        return "BASICDUMMY";
    if (address == (uint64_t)&CSRRCExec)
        return "CSRRCExec ";
    if (address == (uint64_t)&MULExec)
        return "MULExec   ";
    if (address == (uint64_t)&MULHExec)
        return "MULHExec  ";
    if (address == (uint64_t)&MULHSUExec)
        return "MULHSUExec";
    if (address == (uint64_t)&MULHUExec)
        return "MULHUExec ";
    if (address == (uint64_t)&DIVExec)
        return "DIVExec   ";
    if (address == (uint64_t)&DIVUExec)
        return "DIVUExec  ";
    if (address == (uint64_t)&REMExec)
        return "REMExec   ";
    if (address == (uint64_t)&REMUExec)
        return "REMUExec  ";
    if (address == (uint64_t)&DUMMYExec)
        return "DUMMYExec ";

    return "HER ZNAET ";
}

void Sim::Execute ()
{
    std::map<uint32_t, uint32_t> bb_map;
    std::map<std::pair<uint64_t, uint64_t>, uint32_t> instr_map;
    std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
    Instruction dec_instr;
    try
    {
        uint32_t cur_instr_addr = 0;
        BasicBlock* BB;
        while (true)
        {
            cur_instr_addr = hart_state.GetPc();

            auto it = bb_map.find(cur_instr_addr);
            if (it != bb_map.end())
                bb_map[cur_instr_addr] = it->second + 1;
            else
                bb_map[cur_instr_addr] = 1;
            
            BB = InstrCache.get(cur_instr_addr);
            if (BB == NULL)
            {
                BasicBlock BB_new = BasicBlock (hart_state, DCD);
                InstrCache.put (cur_instr_addr, BB_new);
                BB = &BB_new;
            }

            BB->InstrMapHandler (instr_map);

            BB->ExecuteBlock (hart_state);
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

    std::vector< std::pair< uint32_t, uint32_t > > bb_vec(bb_map.begin(), bb_map.end() );
    std::sort(bb_vec.begin(), bb_vec.end(), bb_pred);
    printf("Basic block statistics:\n");
    for (auto p : bb_vec)
        printf("BB start: 0x%x\tscore: %d\n", p.first, p.second);

    std::vector< std::pair< std::pair<uint64_t, uint64_t>, uint32_t > > instr_vec(instr_map.begin(), instr_map.end() );
    std::sort(instr_vec.begin(), instr_vec.end(), instr_pred);
    printf("Instruction pair statistics:\n");
    for (auto p : instr_vec)
        printf("%s\t%s\tscore: %d\n", AddrToString(p.first.first), AddrToString(p.first.second), p.second);
}