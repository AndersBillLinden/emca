#include "disassembler.h"
#include "opcodes.h"
#include <string>

#include "end_of_file_exception.h"

using namespace std;

disassembler::disassembler(const char *filename): file(infile(filename))
{}

int to_signed_byte(int input)
{
	return input > 127 ? input - 256 : input;
}

void disassembler::run()
{	
	int chr = EOF;
	int offset;
	char buffer[128];

	try
	{
		offset = file.read_ushort();
	}
	
	catch(end_of_file_exception &e)
	{
		puts("; incorrect input file, < 2 bytes\n");
		return;
	}

	printf("!to \"result.prg\",cbm\n* = $%04x\n\n", offset);
	
	try
	{
		for (;;)
		{
			file.mark();
			
			chr = file.read_byte();
			
			const opcode &code = opcodes[chr];
			
			printf("_%04x  ", offset);
						
			switch(code.addressing)
			{
				case NONE:
					sprintf(buffer, "%s", code.mnemonic);
					break;
				case IZX:
					sprintf(buffer, "%s ($%02x,x)", code.mnemonic, file.read_byte());
					offset++;
					break;
				case ZP:
					sprintf(buffer, "%s $%02x", code.mnemonic, file.read_byte());
					offset++;
					break;
				case IMM:
					sprintf(buffer, "%s #$%02x", code.mnemonic, file.read_byte());
					offset++;
					break;
				case ABS:
					sprintf(buffer, "%s $%04x", code.mnemonic, file.read_ushort());
					offset += 2;
					break;
				case REL:
					sprintf(buffer, "%s $%04x", code.mnemonic, offset + 2 + to_signed_byte(file.read_byte()));
					offset++;
					break;
				case IZY:
					sprintf(buffer, "%s ($%02x),y", code.mnemonic, file.read_byte());
					offset++;
					break;
				case ZPX:
					sprintf(buffer, "%s $%02x,x", code.mnemonic, file.read_byte());
					offset++;
					break;
				case ABY:
					sprintf(buffer, "%s $%04x,y", code.mnemonic, file.read_ushort());
					offset += 2;
					break;
				case ABX:
					sprintf(buffer, "%s $%04x,x", code.mnemonic, file.read_ushort());
					offset += 2;
					break;
				case IND:
					sprintf(buffer, "%s ($%04x)", code.mnemonic, file.read_ushort());
					offset += 2;
					break;
				case ZPY:
					sprintf(buffer,"%s $%02x,y", code.mnemonic, file.read_byte());
					offset++;
			}
			
			offset++;
			
			if (code.valid == INVALID)
				output_bytes_in_start_of_line();
			
			fputs(buffer,stdout);
			
			if (code.valid == VALID)
				output_bytes_in_end_of_line();
			
			putchar('\n');
		}
	}
	catch(end_of_file_exception &e)
	{
		if (file.has_bytes_since_mark())
			output_bytes_in_start_of_line();		
	}
}

void disassembler::output_bytes_in_start_of_line()
{
	list<int> bytes = file.get_bytes_since_mark();
	
	fputs("!byte", stdout);
	
	output_bytes(bytes);
	
	fputs("; ", stdout);
}

void disassembler::output_bytes_in_end_of_line()
{
	list<int> bytes = file.get_bytes_since_mark();

	fputs("\t;", stdout);	
	
	output_bytes(bytes);
}

void disassembler::output_bytes(list<int> bytes)
{
	bool first = true;
	
	for (list<int>::iterator iter = bytes.begin();
		iter!= bytes.end();
		iter++)
	{
		if (first)
			first = false;
	  else
			putchar(',');
		printf(" $%02x", *iter);
	}
}
