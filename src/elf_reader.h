#ifndef ELF_READER_H
#define ELF_READER_H

#include <iostream>
#include <iomanip>
#include <err.h>
#include <fcntl.h>
#include <gelf.h>
#include <unistd.h>
#include <vector>

class Elf_reader
{
private:
    int fd = -1;
	Elf *e = nullptr;
	GElf_Ehdr ehdr;

	size_t n_ph = 0;
	std::vector<GElf_Phdr> phdrs;
	
	size_t shstrndx;
	std::vector<GElf_Shdr> shdrs;

public:
    Elf_reader() {}
    void Init(const char *file_name);
    void PrintEhdr();
    void PrintPhdrs();
    void PrintShdrs();
    void LoadSegments(std::vector<uint32_t> &instructions);
    void LoadSections(std::vector<uint32_t> &instructions);
    ~Elf_reader();
};

#endif