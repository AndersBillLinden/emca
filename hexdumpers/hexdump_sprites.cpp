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

int dump_pre_data(FILE *file, int offset)
{
	int pre_amount = offset % 64;

	if (pre_amount > 0)
	{
		printf("_%04x !byte ", offset);
		bool first = true;
		for (int i = pre_amount; i < 64; i++)
		{
			int chr = fgetc(file);
			if (chr == EOF)
				break;
		
			offset++;
			if (first)
				first = false;
			else
				putchar(',');
			
			printf("$%02x", chr);
		}
	}
	
	putchar('\n');
	
	return offset;
}

int dump_post_data(FILE *file, int offset)
{
  bool printed_address = false;

	int chr;
	
	bool first = true;
	while ((chr = fgetc(file)) != EOF)
	{
		if (!printed_address)
		{
			printf("_%04x !byte ", offset);
			printed_address =  true;
		}

		if (first)
			first = false;
		else
			putchar(',');
			
		printf("$%02x", chr);
	}
	
	putchar('\n');
	
	return offset;
}

int dump_sprite_data(FILE *file, int offset)
{
	int amount;
	unsigned char buffer[64];
	while ((amount = fread(buffer, 1, 64, file)) > 0)
	{
		if (amount < 64)
		{
			fseek(file, offset, SEEK_SET);
			break;
		}
			
		for (int i = 0; i < 21; i++)
		{
			printf("_%04x !byte ", offset);

			for (int j = 0; j < 3; j++)
			{
				if (j > 0)
					putchar(',');
				printf("$%02x", buffer[i * 3 + j]);
			}
				
			fputs(";  ", stdout);
			
			for (int j = 0; j < 3; j++)
			{
				unsigned char c = buffer[i * 3 + j];
				
				for (int k = 0; k < 8; k++)
				{
					fputs((c & 128) == 0 ? "  " : "##", stdout);
					c <<= 1;
				}
			}
			
			offset += 3;
			putchar('\n');
		}

		printf("_%04x !byte $%02x\n\n", offset + 63, buffer[63]);

		putchar('\n');
		
		offset ++;
	}
	
	putchar('\n');
	
	return offset;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fputs("Syntax: hexdump <infile.bin>\n", stderr);
		return 1;
	}
	
	FILE *file = fopen(argv[1], "rb");
	
	int offset = read_ushort(file);
	
	printf("* = $%04x\n\n", offset);
	
	offset = dump_pre_data(file, offset);
	
	offset = dump_sprite_data(file, offset);
	
	dump_post_data(file, offset);
	
	fclose(file);
	
	return 0;
}
