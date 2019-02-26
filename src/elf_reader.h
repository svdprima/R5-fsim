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

public:
    Elf_reader() {}
    void Init(const char *file_name);
    uint32_t Entry();
    void Load(std::vector<uint32_t> &words);
    ~Elf_reader();
};

#endif