#include <cstdio>
#include <fstream>
#include "disassembler.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fputs("Syntax: emca <infile.bin>\n", stderr);
		return 1;
	}

	disassembler d(argv[1]);

	d.run();
	
	return 0;
}
