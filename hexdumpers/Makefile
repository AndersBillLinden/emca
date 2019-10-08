all: hexdump_petscii hexdump_screencode hexdump_sprites

hexdump_petscii: hexdump_petscii.cpp
	g++ -s hexdump_petscii.cpp -o hexdump_petscii

hexdump_screencode: hexdump_screencode.cpp
	g++ -s hexdump_screencode.cpp -o hexdump_screencode

hexdump_sprites: hexdump_sprites.cpp
	g++ -s hexdump_sprites.cpp -o hexdump_sprites


.PHONY : clean

clean:
	-rm hexdump_petscii hexdump_screencode hexdump_sprites