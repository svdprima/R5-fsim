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
    uint32_t cmd_counter;
    MMU _MMU;
public:
    HartState(uint32_t initial_pc, std::vector<uint32_t> &words, uint32_t n_pages)
    : cmd_counter(0), _MMU(words, n_pages)
    {
        pc = initial_pc;
        for(int i = 0; i < 32; ++i)
        {
            if (i != 2)
                regs[i] = 0;
            else
                regs[i] = 0x4ffc; //initialising stack pointer
        }
    }
    void SetPc(uint32_t pc_value)
    {
        pc = pc_value;
    }
    void SetSatp(uint32_t satp_value)
    {
        _MMU.SetSatp(satp_value);
    }
    void SetReg(uint8_t reg_num, uint32_t reg_value)
    {
        if(reg_num > 32)
            errx(EXIT_FAILURE, "Register number is bigger than 32.");
        if(reg_num != 0)
            regs[reg_num] = reg_value;
    }
    inline void WriteWord(uint32_t va, uint32_t data)
    {
        _MMU.WriteWord(va, data);
    }
    inline void WriteHalfWord(uint32_t va, uint16_t data)
    {
        _MMU.WriteHalfWord(va, data);
    }
    inline void WriteByte(uint32_t va, uint8_t data)
    {
        _MMU.WriteByte(va, data);
    }
    void MemDump()
    {
        _MMU.MemDump();
    }
    inline uint32_t GetPc()
    {
        return pc;
    }
    inline uint32_t GetSatp()
    {
        return _MMU.GetSatp();
    }
    inline uint32_t GetReg(uint8_t reg_num)
    {
        if(reg_num > 32)
            errx(EXIT_FAILURE, "Register number is bigger than 32.");
        return regs[reg_num];
    }
    inline uint32_t ReadWord(uint32_t va)
    {
        return _MMU.ReadWord(va);
    }
    uint16_t ReadHalfWord(uint32_t va)
    {
        return _MMU.ReadHalfWord(va);
    }
    inline uint8_t ReadByte(uint32_t va)
    {
        return _MMU.ReadByte(va);
    }
    inline uint32_t Fetch(uint32_t va)
    {
        return _MMU.Fetch(va);
    }
	void PrintPc()
    {
        printf ("The PC is %x\n", pc);
    }
    void PrintSatp()
    {
        _MMU.PrintSatp();
    }
	void PrintReg(uint32_t reg_num)
    {
        if (reg_num >= 32)
            printf("Invalid reg number!\n");
        printf ("Register #%d: %x\n", reg_num, regs[reg_num]);
    }
    void PrintWord(uint32_t va)
    {
        printf ("Word at specified adress: %x\n", ReadWord(va));
    }
    inline void IncreaseCmdCount(uint32_t incr)
    {
        cmd_counter += incr;
    }
    inline uint32_t GetCmdCount ()
    {
        return cmd_counter;
    }
    ~HartState() {}
};

#endif
