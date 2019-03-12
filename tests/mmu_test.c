#include "mmu.h"

int main()
{
	SetRootPPN(0x0);

	FirstLevelPtCnfg(0x10, 0x1, next_level);
	SecondLevelPtCnfg(0x10, 0x10, x_only); // for current code
	SecondLevelPtCnfg(0x11, 0x11, r_w);    // for 0x11c98
	SecondLevelPtCnfg(0x4, 0x4, r_w); // for stack

	FirstLevelPtCnfg(0x100f, 0x2, next_level);
	SecondLevelPtCnfg(0x100f, 0x9, r_w);

	FirstLevelPtCnfg(0x80200, 0x3, next_level);
	SecondLevelPtCnfg(0x80200, 0x9, r_only);

	EnableTranslation();
	

	*(uint32_t*)0x0100faa0 = 0xdeadbeef;
	if(*(uint32_t*)0x80200aa0 != 0xdeadbeef)
		while(1) {}


	return 0;
}