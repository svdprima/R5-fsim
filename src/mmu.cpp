#include "mmu.h"
#include "aux.hpp"

MMU::MMU(std::vector<uint32_t> &words, uint32_t n_pages) 
: R_TLB(64), W_TLB(64), X_TLB(64)
{
	max_pa = n_pages*PAGESIZE;
	if(words.size()*sizeof(uint32_t) > max_pa)
		errx(EXIT_FAILURE, "Not enough pages, address 0x%#010x doesn't fit.", 
									(uint32_t)(words.size()*sizeof(uint32_t)));
	mem.resize(max_pa >> 2);
	mem.insert(mem.begin(), words.begin(), words.end());

	satp = 0x00000000;
}



void MMU::MemDump()
{
	std::ofstream fout("./mem_dump.bin", std::ios::out | std::ios::binary);
	fout.write((char*)&mem[0], mem.size() * sizeof(uint32_t));
	fout.close();
}



uint64_t MMU::Translate(uint32_t va, AccessType access)
{
	uint64_t a = (satp & 0x003fffff) * PAGESIZE;
	int i = LEVELS - 1;
	uint64_t pte_addr;
	uint32_t pte;

	while(1)
	{
		pte_addr = a + (i ? va >> 22 : ((va << 10) >> 22)) * PTESIZE;
		pte = ReadWordPhys(pte_addr);

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

	uint64_t pa = va & 0xfff;
	if(i > 0)
	{
		pa |= va & 0x3ff000;
		pa |= (uint64_t)(pte & 0xfff00000) << 2;
	}
	else
		pa |= (uint64_t)(pte & 0xfffffc00) << 2;

	return pa;
}