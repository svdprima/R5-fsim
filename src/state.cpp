#include "state.h"

State::State(uint32_t initial_pc, std::vector<uint32_t> &instructions)
{
	pc = initial_pc;
	for(int i = 0; i < 32; ++i)
	{
		if (i != 2)
			regs[i] = 0;
		else
			regs[i] = 5000; //initialising stack pointer
	}
	mem.resize(instructions.size()*sizeof(uint32_t));
	memcpy(&mem[0], (void*)instructions.data(), instructions.size()*sizeof(uint32_t));
}



void State::SetPc(uint32_t pc_value)
{
	pc = pc_value;
}



void State::SetReg(uint8_t reg_num, uint32_t reg_value)
{
	if(reg_num > 32)
		errx(EXIT_FAILURE, "Register number is bigger than 32.");
	if(reg_num != 0)
		regs[reg_num] = reg_value;
}



void State::WriteWord(uint32_t addr, uint32_t data)
{
	if(addr+3 > mem.size())
		errx(EXIT_FAILURE, "Out of physical memory, addr - %#010x.", addr);
	mem[addr] = (uint8_t)data;
	mem[addr + 1] = (uint8_t)(data >> 8);
	mem[addr + 2] = (uint8_t)(data >> 16);
	mem[addr + 3] = (uint8_t)(data >> 24);
}



void State::WriteHalfWord(uint32_t addr, uint16_t data)
{
	if(addr+1 > mem.size())
		errx(EXIT_FAILURE, "Out of physical memory, addr - %#010x.", addr);
	mem[addr]       = (uint8_t)data;
	mem[addr + 1]   = (uint8_t)(data >> 8);
}



void State::WriteByte(uint32_t addr, uint8_t data)
{
	if(addr > mem.size())
		errx(EXIT_FAILURE, "Out of physical memory, addr - %#010x.", addr);
	mem[addr] = data;
}



void State::MemDump()
{
	std::ofstream fout("./mem_dump.txt", std::ios::out | std::ios::binary);
	fout.write((char*)&mem[0], mem.size() * sizeof(uint8_t));
	fout.close();
}



uint32_t State::GetPc()
{
	return pc;
}

uint32_t State::GetReg(uint8_t reg_num)
{
	if(reg_num > 32)
		errx(EXIT_FAILURE, "Register number is bigger than 32.");
	return regs[reg_num];
}



uint32_t State::ReadWord(uint32_t addr)
{
	if(addr+3 > mem.size())
		errx(EXIT_FAILURE, "Out of physical memory, addr - %#010x.", addr);
	return	((uint32_t)mem[addr + 3] << 24) | 
			((uint32_t)mem[addr + 2] << 16) | 
			((uint32_t)mem[addr + 1] << 8)  | 
			 (uint32_t)mem[addr];
}



uint16_t State::ReadHalfWord(uint32_t addr)
{
	if(addr+1 > mem.size())
		errx(EXIT_FAILURE, "Out of physical memory, addr - %#010x.", addr);
	return ((uint16_t)mem[addr + 1] << 8) | 
            (uint16_t)mem[addr];
}



uint8_t State::ReadByte(uint32_t addr)
{
	if(addr > mem.size())
		errx(EXIT_FAILURE, "Out of physical memory, addr - %#010x.", addr);
	return mem[addr];
}

void State::PrintPc()
{
	printf ("The PC is %x\n", pc);
}

void State::PrintReg(uint32_t reg_num)
{
	if (reg_num >= 32)
			printf("Invalid reg number!\n");
	printf ("Register #%d: %x\n", reg_num, regs[reg_num]);
}

void State::PrintWord(uint32_t addr)
{
    printf ("Word at specified adress: %x\n", ReadWord(addr));
}
