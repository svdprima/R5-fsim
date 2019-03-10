#ifndef MMU_H
#define MMU_H

#define PAGESIZE    4096
#define LEVELS      2
#define PTESIZE     4

//PTE bits
#define V_bit       1<<0
#define R_bit       1<<1
#define W_bit       1<<2
#define X_bit       1<<3
#define U_bit       1<<4
#define G_bit       1<<5
#define A_bit       1<<6
#define D_bit       1<<7

#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <err.h>
#include <string.h>
#include <fstream>
#include <stdexcept>
#include "lru_cache.h"

class MMU
{
private:
    uint32_t satp;
    std::vector<uint32_t> mem;
    uint64_t max_pa;
    LRUCache<uint32_t, uint32_t> R_TLB;
    LRUCache<uint32_t, uint32_t> W_TLB;
    LRUCache<uint32_t, uint32_t> X_TLB;

public:
    enum AccessType
    {
        READ,
        WRITE,
        EXEC
    };

    MMU(std::vector<uint32_t> &words, uint32_t n_pages);
    void WriteWord(uint64_t pa, uint32_t data)
    {
        if(pa+3 > max_pa)
            errx(EXIT_FAILURE, "Out of physical memory, pa - %#010lx.", pa);
        if((pa & 0b11) == 0b00)
            mem[pa>>2] = data;
        else
            errx(EXIT_FAILURE, "Unaligned word access, pa - %#010lx.", pa);
    }
    void WriteHalfWord(uint64_t pa, uint16_t data)
    {
        if(pa+1 > max_pa)
            errx(EXIT_FAILURE, "Out of physical memory, pa - %#010lx.", pa);
        if((pa & 0b1) == 0b0)
        {
            uint32_t offset_in_word = (pa & 0b1) * 16;
            mem[pa>>2] = (mem[pa>>2] & ~(0xffff << offset_in_word))
                            | ((uint32_t)data << offset_in_word);
        }
        else
            errx(EXIT_FAILURE, "Unaligned half word access, pa - %#010lx.", pa);
        
    }
    void WriteByte(uint64_t pa, uint8_t data)
    {
        if(pa > max_pa)
            errx(EXIT_FAILURE, "Out of physical memory, pa - %#010lx.", pa);
        uint32_t offset_in_word = (pa & 0b11) * 8;
        mem[pa>>2] = (mem[pa>>2] & ~(0xff << offset_in_word))
                        | ((uint32_t)data << offset_in_word);
    }
    void SetSatp(uint32_t satp_value)
    {
        satp = satp_value;
    }
    void MemDump();
    uint32_t ReadWord(uint64_t pa)
    {
        if(pa+3 > max_pa)
            errx(EXIT_FAILURE, "Out of physical memory, pa - %#010lx.", pa);
        if((pa & 0b11) == 0b00)
            return mem[pa>>2];
        else
            errx(EXIT_FAILURE, "Unaligned word access, pa - %#010lx.", pa);
    }
    uint16_t ReadHalfWord(uint64_t pa)
    {
        if(pa+1 > max_pa)
            errx(EXIT_FAILURE, "Out of physical memory, pa - %#010lx.", pa);
        if((pa & 0b1) == 0b0)
        {
            uint32_t offset_in_word = (pa & 0b1) * 16;
            return (mem[pa>>2] >> offset_in_word) & 0xffff;
        }
        else
            errx(EXIT_FAILURE, "Unaligned half word access, pa - %#010lx.", pa);
    }
    uint8_t ReadByte(uint64_t pa)
    {
        if(pa > max_pa)
            errx(EXIT_FAILURE, "Out of physical memory, pa - %#010lx.", pa);
        uint32_t offset_in_word = (pa & 0b11) * 8;
        return (mem[pa>>2] >> offset_in_word) & 0xff;
    }
    uint32_t GetSatp()
    {
        return satp;
    }
    void PrintSatp()
    {
        printf ("SATP is %x\n", satp);
    }
    uint64_t Translate(uint32_t va, AccessType access);
    ~MMU() {}
};

#endif
