#include "elf_reader.h"

void Elf_reader::Init(const char *file_name)
{
	if(elf_version(EV_CURRENT) == EV_NONE)
		errx(EXIT_FAILURE, "ELF library initialization failed : %s", elf_errmsg(-1));

	if((fd = open(file_name, O_RDONLY, 0)) < 0)
		err(EXIT_FAILURE, "open \" %s \" failed", file_name);

	if((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
		errx(EXIT_FAILURE, "elf_begin () failed : %s.", elf_errmsg(-1));

	if(elf_kind(e) != ELF_K_ELF)
		errx(EXIT_FAILURE, "\" %s \" is not an ELF object.", file_name);

	if(gelf_getehdr(e , &ehdr) == NULL)
		errx(EXIT_FAILURE, "getehdr () failed : %s.", elf_errmsg(-1));

   	if(elf_getphdrnum(e, &n_ph) != 0)
		errx(EXIT_FAILURE, "elf_getphdrnum () failed : %s." , elf_errmsg(-1));

	GElf_Phdr phdr;
	for(int i = 0; i < n_ph; i++)
	{
    	if(gelf_getphdr(e, i, &phdr) != &phdr)
			errx(EXIT_FAILURE, "getphdr () failed : %s.", elf_errmsg(-1));
		phdrs.push_back(phdr);
	}

	Elf_Scn *scn;
	GElf_Shdr shdr;
	if (elf_getshdrstrndx(e, &shstrndx) != 0)
		errx(EXIT_FAILURE, "elf_getshdrstrndx () failed : %s.", elf_errmsg(-1));

	scn = NULL;
	while((scn = elf_nextscn(e, scn)) != NULL)
	{
		if(gelf_getshdr(scn, &shdr) != &shdr)
			errx(EXIT_FAILURE, "getshdr () failed : %s.", elf_errmsg(-1));
		shdrs.push_back(shdr);
	}
}



void Elf_reader::PrintEhdr()
{
	std::cout << "EHDR :" << std::endl;

	std::cout << std::left << std::setw(15) << "architecture" << "  ";
	switch(ehdr.e_ident[EI_CLASS])
	{
	case ELFCLASSNONE:	std::cout << "Invalid class"	<< std::endl; break;
	case ELFCLASS32:	std::cout << "32-bit" 			<< std::endl; break;
	case ELFCLASS64:	std::cout << "64-bit" 			<< std::endl; break;
	default : 			std::cout << "unknown"			<< std::endl; break;
	}

	std::cout << std::setw(15) << "e_type" << ehdr.e_type << "  ";
	switch(ehdr.e_type)
	{
	case ET_NONE:	std::cout << "An unknown type"   	<< std::endl; break;
	case ET_REL: 	std::cout << "A relocatable file" 	<< std::endl; break;
	case ET_EXEC:  	std::cout << "An executable file"   << std::endl; break;
	case ET_DYN: 	std::cout << "A shared object" 		<< std::endl; break;
	case ET_CORE: 	std::cout << "A core file"			<< std::endl; break;
	default : 		std::cout << "unknown"				<< std::endl; break;
	}

	std::cout << std::setw(15) << "e_machine" << ehdr.e_machine << "  ";
	switch(ehdr.e_machine)
	{
	case EM_NONE:			std::cout << "An unknown machine"   				<< std::endl; break;
	case EM_RISCV:			std::cout << "RISC-V" 								<< std::endl; break;
	case EM_M32: 			std::cout << "AT&T WE 32100" 						<< std::endl; break;
	case EM_SPARC:  		std::cout << "Sun Microsystems SPARC"   			<< std::endl; break;
	case EM_386: 			std::cout << "Intel 80386" 							<< std::endl; break;
	case EM_68K: 			std::cout << "Motorola 68000" 						<< std::endl; break;
	case EM_88K: 			std::cout << "Motorola 88000" 						<< std::endl; break;
	case EM_860: 			std::cout << "Intel 80860" 							<< std::endl; break;
	case EM_MIPS: 			std::cout << "MIPS RS3000 (big-endian only)" 		<< std::endl; break;
	case EM_PARISC: 		std::cout << "HP/PA" 								<< std::endl; break;
	case EM_SPARC32PLUS:	std::cout << "SPARC with enhanced instruction set"	<< std::endl; break;
	case EM_PPC: 			std::cout << "PowerPC" 								<< std::endl; break;
	case EM_PPC64: 			std::cout << "PowerPC 64-bit" 						<< std::endl; break;
	case EM_S390: 			std::cout << "IBM S/390" 							<< std::endl; break;
	case EM_ARM: 			std::cout << "Advanced RISC Machines" 				<< std::endl; break;
	case EM_SH: 			std::cout << "Renesas SuperH" 						<< std::endl; break;
	case EM_SPARCV9: 		std::cout << "SPARC v9 64-bit" 						<< std::endl; break;
	case EM_IA_64: 			std::cout << "Intel Itanium" 						<< std::endl; break;
	case EM_X86_64: 		std::cout << "AMD x86-64" 							<< std::endl; break;
	case EM_VAX: 			std::cout << "DEC Vax" 								<< std::endl; break;
	default : 				std::cout << "unknown"								<< std::endl; break;
	}

	std::cout << std::setw(15) << "e_version" << ehdr.e_version << "  ";
	switch(ehdr.e_version)
	{
	case EV_NONE:		std::cout << "Invalid version"  << std::endl; break;
	case EV_CURRENT:	std::cout << "Current version" 	<< std::endl; break;
	default : 			std::cout << "unknown"			<< std::endl; break;
	}

	std::cout << std::setw(15) << "e_entry" 	<< ehdr.e_entry		<< std::endl;
	std::cout << std::setw(15) << "e_phoff" 	<< ehdr.e_phoff 	<< std::endl;
	std::cout << std::setw(15) << "e_shoff" 	<< ehdr.e_shoff 	<< std::endl;
	std::cout << std::setw(15) << "e_flags" 	<< ehdr.e_flags 	<< std::endl;
	std::cout << std::setw(15) << "e_ehsize" 	<< ehdr.e_ehsize 	<< std::endl;
	std::cout << std::setw(15) << "e_phentsize" << ehdr.e_phentsize << std::endl;
	std::cout << std::setw(15) << "e_shentsize" << ehdr.e_shentsize << std::endl;

	std::cout << std::endl;
}



void Elf_reader::PrintPhdrs()
{
	if(n_ph == 0)
		std::cout << "no PHDR" << std::endl << std::endl;
	else
		for(int i = 0; i < n_ph; i++)
	    {
	    	std::cout << "PHDR " << i << " :" << std::endl;

	    	std::cout << std::left << std::setw(15) << "p_type" << phdrs[i].p_type << "  ";
	    	switch(phdrs[i].p_type)
	    	{
	    	case PT_NULL:   		std::cout << "NULL"   		<< std::endl; break;
	    	case PT_INTERP: 		std::cout << "INTERP" 		<< std::endl; break;
	    	case PT_PHDR:   		std::cout << "PHDR"   		<< std::endl; break;
	    	case PT_SUNWBSS: 		std::cout << "SUNWBSS" 		<< std::endl; break;
	    	//case PT_SUNWCAP: 		std::cout << "SUNWCAP" 		<< std::endl; break;
	    	case PT_LOAD:   		std::cout << "LOAD"   		<< std::endl; break;
	    	case PT_NOTE:   		std::cout << "NOTE"  		<< std::endl; break;
	    	case PT_TLS:   			std::cout << "TLS"   		<< std::endl; break;
	    	case PT_SUNWSTACK:		std::cout << "SUNWSTACK"   	<< std::endl; break;
	    	case PT_DYNAMIC:   		std::cout << "DYNAMIC"  	<< std::endl; break;
	    	case PT_SHLIB:			std::cout << "SHLIB"   		<< std::endl; break;
	    	//case PT_SUNW_UNWIND:	std::cout << "SUNW_UNWIND"	<< std::endl; break;
	    	//case PT_SUNWDTRACE:	std::cout << "SUNWDTRACE"   << std::endl; break;
	    	default : 				std::cout << "unknown" 		<< std::endl; break;
	    	}
	  	
	    	std::cout << std::setw(15) << "p_offset" << phdrs[i].p_offset << std::endl;
	    	std::cout << std::setw(15) << "p_vaddr"  << phdrs[i].p_vaddr  << std::endl;
	    	std::cout << std::setw(15) << "p_paddr"  << phdrs[i].p_paddr  << std::endl;
	    	std::cout << std::setw(15) << "p_filesz" << phdrs[i].p_filesz << std::endl;
	    	std::cout << std::setw(15) << "p_memsz"  << phdrs[i].p_memsz  << std::endl;

	    	std::cout << std::setw(15) << "p_flags" << phdrs[i].p_flags << "  ";
	    	if(phdrs[i].p_flags & PF_X)
				std::cout << "execute" << std::endl;
			if(phdrs[i].p_flags & PF_R)
				std::cout << "read"    << std::endl;
			if(phdrs[i].p_flags & PF_W)
				std::cout << "write"   << std::endl;
			
			std::cout << std::setw(15) << "p_align"  << phdrs[i].p_align  << std::endl;

			std::cout << std::endl;
	    }
}



void Elf_reader::PrintShdrs()
{
	std::cout << "SHDRS :" << std::endl;
	for(int i = 0; i < shdrs.size(); i++)
		std::cout << std::left << std::setw(5) << i << elf_strptr(e, shstrndx, shdrs[i].sh_name) << std::endl;
	std::cout << std::endl;
}



void Elf_reader::LoadSegments(std::vector<uint32_t> &instructions)
{
	/*if(ehdr.e_machine != EM_RISCV)
    	errx(EXIT_FAILURE, "\" %s \" is not a RISCV machine.", file_name);

    if(ehdr.e_ident[EI_CLASS] != ELFCLASS32)
    	errx(EXIT_FAILURE, "\" %s \" is not a 32 bit machine.", file_name);*/

	for(int i = 0; i < n_ph; i++)
	{
		std::vector<uint32_t> buf(phdrs[i].p_memsz);
		if(read(fd, &(buf[0]), phdrs[i].p_filesz) < 0)
			errx(EXIT_FAILURE, "read() failed : %s." , elf_errmsg(-1));
		instructions.insert(instructions.end(), buf.begin(), buf.end());
	}
}

void Elf_reader::LoadSections(std::vector<uint32_t> &instructions)
{
	Elf_Data *data = NULL;
	Elf_Scn *scn = NULL;

	/*if(ehdr.e_machine != EM_RISCV)
    	errx(EXIT_FAILURE, "\" %s \" is not a RISCV machine.", file_name);

    if(ehdr.e_ident[EI_CLASS] != ELFCLASS32)
    	errx(EXIT_FAILURE, "\" %s \" is not a 32 bit machine.", file_name);*/

	/*while((scn = elf_nextscn(e, scn)) != NULL)
	{
		while((data = elf_getdata(scn, data)) != NULL)
		{
			std::vector<uint32_t> buf((char *)data->d_buf, (char *)data->d_buf + data->d_size);
			instructions.insert(instructions.end(), buf.begin(), buf.end());
		}
	}*/
}

Elf_reader::~Elf_reader()
{
	elf_end(e);
	close(fd);
}