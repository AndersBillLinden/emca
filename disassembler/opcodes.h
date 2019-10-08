enum addressing_mode
{
  NONE, IZX, ZP, IMM, ABS, REL, IZY, ZPX, ABY, ABX, IND, ZPY
};

enum is_instruction_valid
{
  VALID,
  INVALID
};

struct opcode
{
  const char *mnemonic;
  int addressing;
  is_instruction_valid valid;
};

extern const opcode opcodes[256];
