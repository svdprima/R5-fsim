#ifndef SIM_HPP
#define SIM_HPP

#include <vector>
#include "hart_state.h"
#include "decoder.hpp"
#include "aux.hpp"

class BasicBlock
{
private:
    static constexpr uint32_t block_size = 16; //not including BASICBLOCK DUMMY
    std::array<Instruction, block_size + 1> instructions;
public:
    BasicBlock() = default;
    BasicBlock (HartState &h_state, Decoder &DCD)
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
    void ExecuteBlock (HartState& h_state)
    {
        instructions.front().ExecCommand(&(instructions.front()), &h_state);     
    }

    void InstrMapHandler (std::map<std::pair<uint64_t, uint64_t>, uint32_t>& instr_map)
    {
        uint32_t i = 0;
        do 
        {
            if (i > 0)
            {
                uint64_t opcode1 = (uint64_t)instructions[i-1].GetCmd();
                uint64_t opcode2 = (uint64_t)instructions[i].GetCmd();
                auto it = instr_map.find(std::make_pair(opcode1, opcode2));
                if (it != instr_map.end())
                    instr_map[std::make_pair(opcode1, opcode2)] = it->second + 1;
                else
                    instr_map[std::make_pair(opcode1, opcode2)] = 1;
            }
            i++;
        }
        while ((i < block_size) && instructions[i - 1].GetBBEnd());
    }
};

class Sim
{
private:
    LRUCache<uint32_t, BasicBlock> InstrCache;
    HartState hart_state;
    Decoder DCD;
    static constexpr uint8_t cache_size  = 32;
public:
    Sim (HartState &h_state) : InstrCache(cache_size), hart_state(h_state)
    {};
    void Execute ();
};

#endif
