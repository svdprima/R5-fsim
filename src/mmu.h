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
    std::vector<uint8_t> mem;
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
    void WriteWord(uint64_t pa, uint32_t data);
    void WriteHalfWord(uint64_t pa, uint16_t data);
    void WriteByte(uint64_t pa, uint8_t data);
    void SetSatp(uint32_t satp_value);
    void MemDump();
    uint32_t ReadWord(uint64_t pa);
    uint16_t ReadHalfWord(uint64_t pa);
    uint8_t ReadByte(uint64_t pa);
    uint32_t GetSatp();
    void PrintSatp();
    uint64_t Translate(uint32_t va, AccessType access);
    ~MMU() {}
};

#endif
