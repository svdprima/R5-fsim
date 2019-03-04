#include "mmu.h"
#include "aux.hpp"

MMU::MMU(std::vector<uint32_t> &words, uint32_t n_pages)
{
	if(words.size()*sizeof(uint32_t) > n_pages*PAGESIZE)
		errx(EXIT_FAILURE, "Not enough pages, address 0x%#010x doesn't fit.", 
									(uint32_t)(words.size()*sizeof(uint32_t)));
	mem.resize(n_pages*PAGESIZE);
	memcpy(&mem[0], (void*)words.data(), words.size()*sizeof(uint32_t));

	satp = 0x00000000;
}



void MMU::WriteWord(uint64_t pa, uint32_t data)
{
	if(pa+3 > mem.size())
		errx(EXIT_FAILURE, "Out of physical memory, pa - %#010lx.", pa);
	mem[pa] = (uint8_t)data;
	mem[pa + 1] = (uint8_t)(data >> 8);
	mem[pa + 2] = (uint8_t)(data >> 16);
	mem[pa + 3] = (uint8_t)(data >> 24);
}



void MMU::WriteHalfWord(uint64_t pa, uint16_t data)
{
	if(pa+1 > mem.size())
		errx(EXIT_FAILURE, "Out of physical memory, pa - %#010lx.", pa);
	mem[pa]       = (uint8_t)data;
	mem[pa + 1]   = (uint8_t)(data >> 8);
}



void MMU::WriteByte(uint64_t pa, uint8_t data)
{
	if(pa > mem.size())
		errx(EXIT_FAILURE, "Out of physical memory, pa - %#010lx.", pa);
	mem[pa] = data;
}



void MMU::SetSatp(uint32_t satp_value)
{
	satp = satp_value;
}



void MMU::MemDump()
{
	std::ofstream fout("./mem_dump.bin", std::ios::out | std::ios::binary);
	fout.write((char*)&mem[0], mem.size() * sizeof(uint8_t));
	fout.close();
}



uint32_t MMU::ReadWord(uint64_t pa)
{
	if(pa+3 > mem.size())
		errx(EXIT_FAILURE, "Out of physical memory, pa - %#010lx.", pa);
	return	((uint32_t)mem[pa + 3] << 24) | 
			((uint32_t)mem[pa + 2] << 16) | 
			((uint32_t)mem[pa + 1] << 8)  | 
			 (uint32_t)mem[pa];
}



uint16_t MMU::ReadHalfWord(uint64_t pa)
{
	if(pa+1 > mem.size())
		errx(EXIT_FAILURE, "Out of physical memory, pa - %#010lx.", pa);
	return ((uint16_t)mem[pa + 1] << 8) | 
            (uint16_t)mem[pa];
}



uint8_t MMU::ReadByte(uint64_t pa)
{
	if(pa > mem.size())
		errx(EXIT_FAILURE, "Out of physical memory, pa - %#010lx.", pa);
	return mem[pa];
}



uint32_t MMU::GetSatp()
{
	return satp;
}

void MMU::PrintSatp()
{
    printf ("SATP is %x\n", satp);
}


uint64_t MMU::Translate(uint32_t va, AccessType access)
{
	if(satp >> 31 == 0)
		return (uint64_t)va;

	uint64_t a = (satp & 0x003fffff) * PAGESIZE;
	int i = LEVELS - 1;
	uint64_t pte_addr;
	uint32_t pte;

	while(1)
	{
		pte_addr = a + (i ? va >> 22 : ((va << 10) >> 22)) * PTESIZE;
		pte = ReadWord(pte_addr);

		if((pte & V_bit) == 0)
	        errx(EXIT_FAILURE, "page fault (invalid), pte - %#010x, pte_addr - %#010lx.", pte, pte_addr);

		if(((pte & R_bit) == 0) && ((pte & W_bit) == W_bit))
			errx(EXIT_FAILURE, "page fault (W, but not R), pte - %#010x, pte_addr - %#010lx.", pte, pte_addr);

		if(((pte & R_bit) == R_bit) || ((pte & X_bit) == X_bit))
			break;

		i = i - 1;
		if(i < 0)
			errx(EXIT_FAILURE, "page fault (i<0), pte - %#010x, pte_addr - %#010lx.", pte, pte_addr);
		
		a = (uint64_t)(pte >> 10) * PAGESIZE;
	}
	
	//leaf PTE has been found
	if((access == READ 	&& (pte & R_bit) == 0) || 
	   (access == WRITE	&& (pte & W_bit) == 0) || 
	   (access == EXEC 	&& (pte & X_bit) == 0))
		errx(EXIT_FAILURE, "page fault (access type), pte - %#010x, pte_addr - %#010lx.", pte, pte_addr);

	if((i > 0) && (((pte >> 10) & 0x3ff) != 0))
		errx(EXIT_FAILURE, "page fault (superpage), pte - %#010x, pte_addr - %#010lx.", pte, pte_addr);

	if((pte & A_bit) == 0)
		errx(EXIT_FAILURE, "page fault (access bit), pte - %#010x, pte_addr - %#010lx.", pte, pte_addr);
	
	if((access == WRITE) && ((pte & D_bit) == 0))
		errx(EXIT_FAILURE, "page fault (dirty bit), pte - %#010x, pte_addr - %#010lx.", pte, pte_addr);

	uint64_t pa;
	pa = (uint64_t)va & 0xfff;
	if(i > 0)
	{
		pa |= va & 0x3ff000;
		pa |= (uint64_t)(pte & 0xfff00000) << 2;
	}
	else
		pa |= (uint64_t)(pte & 0xfffffc00) << 2;
	return pa;
}
