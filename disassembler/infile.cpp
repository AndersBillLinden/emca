#include "infile.h"
#include "end_of_file_exception.h"

infile::infile(const char *filename)
{
	file = fopen(filename, "rb");
}

int infile::read_byte()
{
	int chr = fgetc(file);
	
	if (chr == EOF)
		throw end_of_file_exception();
	else
		bytes_since_mark.push_back(chr);

	return chr;
}

int infile::read_ushort()
{
	int chr1 = fgetc(file);
	int chr2 = fgetc(file);
	
	if (chr2 == EOF)
	{
		if (chr1 != EOF)
			bytes_since_mark.push_back(chr1);

		throw end_of_file_exception();
	}
	else
	{
		bytes_since_mark.push_back(chr1);
		bytes_since_mark.push_back(chr2);
	}
	
	return chr1 + chr2 * 256;
}

void infile::mark()
{	bytes_since_mark.clear(); }

bool infile::has_bytes_since_mark()
{ return bytes_since_mark.size() > 0; }

const list<int> infile::get_bytes_since_mark()
{ return bytes_since_mark; }
