#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>

using namespace std;

const char *conversionmap =
	"@abcdefghijklmnopqrstuvwxyz[£].. !\"#$%&´()*+,-./0123456789:;<=>?"
	".ABCDEFGHIJKLMNOPQRSTUVWXYZ....................................."
	"@abcdefghijklmnopqrstuvwxyz[£].. !\"#$%&´()*+,-./0123456789:;<=>?"
	".ABCDEFGHIJKLMNOPQRSTUVWXYZ.....................................";

int read_ushort(FILE *file)
{
	int chr1 = fgetc(file);
	int chr2 = fgetc(file);
	
	if (chr2 == EOF)
	{
		fputs("Error: truncated infile\n", stderr);
		exit(1);
	}
	
	return chr1 + chr2 * 256;
}

int conv_char(int input)
{	return isprint(input) ? input : '.';	}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fputs("Syntax: hexdump <infile.bin>\n", stderr);
		return 1;
	}

	unsigned char buffer[16];
		
	FILE *file = fopen(argv[1], "rb");
	
	int offset = read_ushort(file);
	
	int amount;
	int blanks = offset % 16;
	
	while ((amount = fread(buffer, 1, 16 - blanks, file)) > 0)
	{
		printf("_%04x !byte ", offset);

		for (int i = 0; i < blanks; i++)
			fputs("    ", stdout);		
	
		for (int i = 0; i < amount; i++)
		{
			printf("$%02x", (int)buffer[i]);
			
			if (i < amount - 1)
				putchar(',');
		}

		for (int i = amount; i < 16 - blanks; i++)
			fputs("    ", stdout);
			
		fputs(" ; ", stdout);

		for (int i = 0; i < blanks; i++)
			putchar(' ');		
		
		for (int i = 0; i < amount; i++)
			printf("%c", conversionmap[(int)buffer[i]]);
		
		puts(" ");

		offset += amount;
		blanks = 0;
	}
	
	fclose(file);
	
	return 0;
}
