#include "hart_state.h"

HartState::HartState(uint32_t initial_pc, std::vector<uint32_t> &words, uint32_t n_pages) 
: _MMU(words, n_pages)
{
	pc = initial_pc;
	for(int i = 0; i < 32; ++i)
	{
		if (i != 2)
			regs[i] = 0;
		else
			regs[i] = 0x4fff; //initialising stack pointer
	}
}

void HartState::SetPc(uint32_t pc_value)
{
	pc = pc_value;
}

void HartState::SetSatp(uint32_t satp_value)
{
	_MMU.SetSatp(satp_value);
}

void HartState::PrintSatp()
{
    _MMU.PrintSatp();
}

void HartState::SetReg(uint8_t reg_num, uint32_t reg_value)
{
	if(reg_num > 32)
		errx(EXIT_FAILURE, "Register number is bigger than 32.");
	if(reg_num != 0)
		regs[reg_num] = reg_value;
}

void HartState::WriteWord(uint32_t va, uint32_t data)
{
	uint64_t pa = _MMU.Translate(va, MMU::AccessType::WRITE);
	_MMU.WriteWord(pa, data);
}

void HartState::WriteHalfWord(uint32_t va, uint16_t data)
{
	uint64_t pa = _MMU.Translate(va, MMU::AccessType::WRITE);
	_MMU.WriteHalfWord(pa, data);	
}

void HartState::WriteByte(uint32_t va, uint8_t data)
{
	uint64_t pa = _MMU.Translate(va, MMU::AccessType::WRITE);
	_MMU.WriteByte(pa, data);	
}

void HartState::MemDump()
{
	_MMU.MemDump();
}

uint32_t HartState::GetPc()
{
	return pc;
}

uint32_t HartState::GetSatp()
{
	return _MMU.GetSatp();
}

uint32_t HartState::GetReg(uint8_t reg_num)
{
	if(reg_num > 32)
		errx(EXIT_FAILURE, "Register number is bigger than 32.");
	return regs[reg_num];
}

uint32_t HartState::ReadWord(uint32_t va)
{
	uint64_t pa = _MMU.Translate(va, MMU::AccessType::READ);
	return _MMU.ReadWord(pa);
}

uint16_t HartState::ReadHalfWord(uint32_t va)
{
	uint64_t pa = _MMU.Translate(va, MMU::AccessType::READ);
	return _MMU.ReadHalfWord(pa);
}

uint8_t HartState::ReadByte(uint32_t va)
{
	uint64_t pa = _MMU.Translate(va, MMU::AccessType::READ);
	return _MMU.ReadByte(pa);
}

uint32_t HartState::Fetch(uint32_t va)
{
	uint64_t pa = _MMU.Translate(va, MMU::AccessType::EXEC);
	return _MMU.ReadWord(pa);
}

void HartState::PrintPc()
{
	printf ("The PC is %x\n", pc);
}

void HartState::PrintReg(uint32_t reg_num)
{
	if (reg_num >= 32)
			printf("Invalid reg number!\n");
	printf ("Register #%d: %x\n", reg_num, regs[reg_num]);
}

void HartState::PrintWord(uint32_t va)
{
    printf ("Word at specified adress: %x\n", ReadWord(va));
}
