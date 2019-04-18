#ifndef SIM_HPP
#define SIM_HPP

#include <vector>
#include "hart_state.h"
#include "decoder.hpp"
#include "aux.hpp"
#include "simple_cache.h"

class BasicBlock
{
private:
    static constexpr uint32_t block_size = 16; //not including BASICBLOCK DUMMY
    std::array<Instruction, block_size + 1> instructions;
public:
    BasicBlock() = default;
    BasicBlock (HartState& h_state, Decoder& DCD) noexcept;
    void ExecuteBlock (HartState& h_state);
};

class Sim
{
private:
    SimpleCache<uint32_t, BasicBlock> InstrCache;
    HartState hart_state;
    Decoder DCD;
public:
    Sim (HartState &h_state) : InstrCache(), hart_state(h_state)
    {};
    void Execute ();
};

#endif
