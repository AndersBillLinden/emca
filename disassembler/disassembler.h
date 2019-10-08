#ifndef __DISASSEMBLER_H
#define __DISASSEMBLER_H

#include <cstdio>
#include <list>
#include "infile.h"

using namespace std;

class disassembler
{
public:
	disassembler(const char *filename);
	void run();
private:
	void output_bytes_in_start_of_line();
	void output_bytes_in_end_of_line();
	void output_bytes(list<int> bytes);
	infile file;
};

#endif
