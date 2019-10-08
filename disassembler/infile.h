#ifndef __INFILE_H
#define __INFILE_H

#include <list>
#include <stdio.h>

using namespace std;

class infile
{
public:
	infile(const char *filename);
	void mark();

	int read_byte();
	int read_ushort();
	const list<int> get_bytes_since_mark();
	bool has_bytes_since_mark();
private:
	FILE *file;
	list<int> bytes_since_mark;
};


#endif
