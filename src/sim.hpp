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
    BasicBlock (HartState& h_state, Decoder& DCD);
    void ExecuteBlock (HartState& h_state);
};

class Sim
{
private:
    LRUCache<uint32_t, BasicBlock> InstrCache;
    HartState hart_state;
    Decoder DCD;
    static constexpr uint8_t cache_size  = 128;
public:
    Sim (HartState &h_state) : InstrCache(cache_size), hart_state(h_state)
    {};
    void Execute ();
};

#endif
