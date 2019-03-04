#ifndef HART_STATE_H
#define HART_STATE_H

#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <err.h>
#include <fstream>
#include "mmu.h"

class HartState
{
private:
    uint32_t pc;
    uint32_t regs[32];
    MMU _MMU;

public:
    HartState(uint32_t initial_pc, std::vector<uint32_t> &words, uint32_t n_pages);
    void SetPc(uint32_t pc_value);
    void SetSatp(uint32_t satp_value);
    void SetReg(uint8_t reg_num, uint32_t reg_value);
    void WriteWord(uint32_t va, uint32_t data);
    void WriteHalfWord(uint32_t va, uint16_t data);
    void WriteByte(uint32_t va, uint8_t data);
    void MemDump();
    uint32_t GetPc();
    uint32_t GetSatp();
    void PrintSatp();
    uint32_t GetReg(uint8_t reg_num);
    uint32_t ReadWord(uint32_t va);
    uint16_t ReadHalfWord(uint32_t va);
    uint8_t ReadByte(uint32_t va);
    uint32_t Fetch(uint32_t va);
	void PrintPc();
	void PrintReg(uint32_t reg_num);
    void PrintWord(uint32_t va);
    ~HartState() {}
};

#endif
