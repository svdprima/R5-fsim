#ifndef SIM_HPP
#define SIM_HPP

#include "hart_state.h"
#include "decoder.hpp"
#include "aux.hpp"

class Sim
{
private:
    HartState hart_state;
    Decoder DCD;
public:
    Sim (HartState &h_state) : hart_state(h_state)
    {};
    void Execute (bool verbose);
};

class BasicBlock
{
private:
    static constexpr uint32_t block_size = 16; //not including BASICBLOCK DUMMY
    std::array<Instruction, block_size + 1> instructions;
public:
    BasicBlock (HartState& h_state, Decoder& DCD);
    void ExecuteBlock (HartState& h_state);
};

#endif
