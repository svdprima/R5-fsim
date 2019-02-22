#ifndef STATE_H
#define STATE_H

#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <err.h>
#include <fstream>
#include <string.h>

class State
{
private:
    uint32_t pc;
    uint32_t regs[32];
    std::vector<uint8_t> mem;

public:
    State(uint32_t initial_pc, std::vector<uint32_t> &instructions);
    void SetPc(uint32_t pc_value);
    void SetReg(uint8_t reg_num, uint32_t reg_value);
    void WriteWord(uint32_t addr, uint32_t data);
    void WriteHalfWord(uint32_t addr, uint16_t data);
    void WriteByte(uint32_t addr, uint8_t data);
    void MemDump();
    uint32_t GetPc();
    uint32_t GetReg(uint8_t reg_num);
    uint32_t ReadWord(uint32_t addr);
    uint16_t ReadHalfWord(uint32_t addr);
    uint8_t ReadByte(uint32_t addr);
	void PrintPc();
	void PrintReg(uint32_t reg_num);
    void PrintWord(uint32_t addr);
    ~State() {}
};

#endif
