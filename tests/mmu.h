#define uint32_t unsigned int

typedef enum Pte_t
{
	next_level	= 0b000,
	r_only		= 0b001,
	r_w			= 0b011,
	x_only		= 0b100,
	r_x			= 0b101,
	r_w_x		= 0b111
} Pte_t;

void SetRootPPN(uint32_t ppn)
{
	ppn &= 0x003fffff;
	uint32_t satp;
	asm("csrrs %[dest], satp, x0" : [dest] "=r" (satp)); // read satp
	satp |= ppn;
	asm("csrrw x0, satp, %[value]" :: [value] "r" (satp)); // write satp
}

void FirstLevelPtCnfg(uint32_t vpn, uint32_t ppn, Pte_t pte_type)
{
	vpn &= 0x000fffff;
	ppn &= 0x003fffff;
	uint32_t satp;
	uint32_t* first_level_pte; // should be 34bit
	asm("csrrs %[dest], satp, x0" : [dest] "=r" (satp)); // read satp
	first_level_pte = (uint32_t*)(((satp & 0x003fffff) << 12) + ((vpn >> 10)) << 2);
	*first_level_pte = (ppn << 10) | (0b1111 << 4) | (pte_type << 1) | 0b1;
}

void SecondLevelPtCnfg(uint32_t vpn, uint32_t ppn, Pte_t pte_type)
{
	vpn &= 0x000fffff;
	ppn &= 0x003fffff;
	uint32_t satp;
	uint32_t* first_level_pte;  // should be 34bit
	uint32_t* second_level_pte; // should be 34bit
	asm("csrrs %[dest], satp, x0" : [dest] "=r" (satp)); // read satp
	first_level_pte = (uint32_t*)(((satp & 0x003fffff) << 12) + ((vpn >> 10)) << 2);
	if(((*first_level_pte >> 1) & 0b111) != next_level)
		return;
	second_level_pte = (uint32_t*)(((*first_level_pte & 0xfffffc00) << 2) 
						+ ((vpn & 0x3ff) << 2));
	*second_level_pte = (ppn << 10) | (0b1111 << 4) | (pte_type << 1) | 0b1;
}

void EnableTranslation()
{
	uint32_t satp;
	asm("csrrs %[dest], satp, x0" : [dest] "=r" (satp)); // read satp
	satp |= (1 << 31);
	asm("csrrw x0, satp, %[value]" :: [value] "r" (satp)); // write satp
}

void DisableTranslation()
{
	uint32_t satp;
	asm("csrrs %[dest], satp, x0" : [dest] "=r" (satp)); // read satp
	satp &= ~(1 << 31);
	asm("csrrw x0, satp, %[value]" :: [value] "r" (satp)); // write satp
}

void InitMMU()
{
	SetRootPPN(0x0);
	FirstLevelPtCnfg(0x10, 0x1, next_level);
	SecondLevelPtCnfg(0x10, 0x10, x_only); // for code
	SecondLevelPtCnfg(0x11, 0x11, r_w); // for exitprocs
	SecondLevelPtCnfg(0x4, 0x4, r_w); // for stack
	EnableTranslation();
}